/**
 **************************************************************************************************
 * @file        bsp_ad7682.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_ad7682.h"
#include "bsp_conf.h"
#include "bsp_ad7682_port.h"
#include "clog.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_power.h"
#include "math.h"
#include "user_task.h"
/**
 * @addtogroup    bsp_ad7682_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad7682_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Macros_Defines 
 * @brief         
 * @{  
 */
//  00 1 111 XXX 1 110 00 1  0x3A71 //实际使用
//  00 1 111 XXX 1 000 00 1  0x3A41 //2.5v内部基准 
#define BSP_AD7682_SAMPLE_CFG 		 0x3A41// 0x3A71 : external 2.5V  ,0x3A41: internal 2.5V
/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Constants_Defines 
 * @brief         
 * @{  
 */
#define BSP_AD7682_CH_QUEUE_LEN 		12
const uint8_t bsp_ad7682_ch_queue[BSP_AD7682_CH_QUEUE_LEN] = {2 ,3, 2, 1, 2, 3, 2, 1} ; //{2 ,3, 2, 1, 2, 3, 2, 1} ;  // real sample fre is 32768 ,so this ch can be 16384 ,8192
const uint8_t bsp_ad7682_ch_data_queue[12]={0,1,0,2,0,1,0,2};


/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Private_Variables 
 * @brief         
 * @{  
 */

uint16_t bsp_ad7682_rec[8] = { 0 };
//uint16_t bsp_ad7682_data[BSP_AD7682_SAMPLE_ADCH * BSP_AD7682_SAMPLEPOINTS*2] = { 0 };
uint16_t bsp_ad7982_cur_ad_index = 0;
uint16_t bsp_ad7682_cur_ad_ch = 0;
uint16_t bsp_ad7682_CurrentAD7682DataCounter = 0;
uint8_t  bsp_ad7682_datareadyprocess = 0 ;

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Functions 
 * @brief         
 * @{  
 */
 
typedef struct 
{
	uint16_t In_0 ;
	uint16_t In_1 ;
	uint16_t In_2 ;
	uint16_t In_3 ;
}BSP_AD7682_Value_t;

BSP_AD7682_Value_t BSP_AD7682_Value = {
	.In_0 = 0,
	.In_1 = 0,
	.In_2 = 0,
	.In_3 = 0,
};

typedef struct
{
	uint8_t cfg[10];
	uint8_t curr_get ; 
	uint8_t real_get ;
	uint8_t check_interval;
}bsp_ad7682_getcmd_queue_t;

const uint8_t BSP_AD7682_UserSequence[] = { 2 };

static uint8_t bsp_ad7682_userseq_ptr = 0;

bsp_ad7682_getcmd_queue_t bsp_ad7682_getcmd_queue = 
{
	.curr_get = 0,
	.real_get = 0,
	.check_interval = 0,
};

 
void BSP_AD7682_Init(void)
{
	BSP_Power_V30_ON();
	BSP_AD7682_Pin_Init();
	BSP_AD7682_Tim_Init();
	DEBUG("BSP_AD7682 is Init\r\n");
}

void BSP_AD7682_LoopTrig(void)
{
	if( (sizeof(BSP_AD7682_UserSequence) / sizeof(BSP_AD7682_UserSequence[0])) > 0 )
	{
		bsp_ad7682_getcmd_queue.cfg[bsp_ad7682_getcmd_queue.curr_get] = BSP_AD7682_UserSequence[bsp_ad7682_userseq_ptr];
		bsp_ad7682_getcmd_queue.check_interval ++ ;
		BSP_AD7682_TriggerGet_IN(bsp_ad7682_getcmd_queue.cfg[bsp_ad7682_getcmd_queue.curr_get]);
		
		bsp_ad7682_userseq_ptr ++ ;
		bsp_ad7682_userseq_ptr %= (sizeof(BSP_AD7682_UserSequence) / sizeof(BSP_AD7682_UserSequence[0]));
		bsp_ad7682_getcmd_queue.curr_get ++ ;
		bsp_ad7682_getcmd_queue.curr_get %= 10;
		
	}
	
}


void BSP_AD7682_GetValue(uint16_t value)
{
	if(bsp_ad7682_getcmd_queue.check_interval == 3)
	{
		bsp_ad7682_getcmd_queue.check_interval -- ;
		
		switch(bsp_ad7682_getcmd_queue.cfg[bsp_ad7682_getcmd_queue.real_get])
		{
			case 0 :
				{
					BSP_AD7682_Value.In_0 = value;
				}
				break;
			case 1 :
				{
					BSP_AD7682_Value.In_1 = value;
				}
				break;
			case 2 :
				{
					BSP_AD7682_Value.In_2 = value;
					BSP_AD7682_CalcRMS( value);
					
					
				}
				break;
			case 3 :
				{
					BSP_AD7682_Value.In_3 = value;
				}
				break;
			default:break;
		}
		bsp_ad7682_getcmd_queue.real_get ++;
		bsp_ad7682_getcmd_queue.real_get %= 10;
	}
}

static uint32_t orignalRMS_value = 0;
static float Value_A = 0.0f;

void BSP_AD7682_CalcRMS(uint16_t value)
{
	static uint16_t count = 0 ;
	
	static uint32_t sum = 0;
	sum  += (value * value );
	
	
	count ++;
	if(count == 20000)
	{
		count  = 0 ;
		sum /= 20000;
		orignalRMS_value = sqrt(sum);
		DEBUG("RMS:%d\r\n" , orignalRMS_value);
		sum = 0;
		
		UserTask_Send_Event(USER_TASK_AD7682_VALUECALC_EVENT)	;	
	}
}

void BSP_AD7682_GetNeedValue(void)
{
	Value_A = (float)(orignalRMS_value * 0.03814697); // 0.03814697 = 2500/65536
}

float BSP_AD7682_GetAvalue(void)
{
	return Value_A;
}


void BSP_AD7682_TriggerGet_IN(uint8_t channel)
{
	if(channel<=3)
	{
		uint16_t ad7682_cfg = 0 ; 
		ad7682_cfg = (uint16_t)BSP_AD7682_SAMPLE_CFG | ( channel << 7 );
		ad7682_cfg = ad7682_cfg << 2;
		BSP_AD7682_WriteCmd(ad7682_cfg);
	}
	else
	{
		
	}
}




// -------------------------------------------------------

void BSP_AD7682_StartGetValue_InConf(void)
{
	uint8_t next_ad_ch = 0;
	uint16_t ad7682_cfg = 0 ; 
	next_ad_ch = bsp_ad7682_ch_queue[bsp_ad7682_cur_ad_ch];

	ad7682_cfg = (uint16_t)BSP_AD7682_SAMPLE_CFG | ( next_ad_ch << 7 );
	//ad7682_cfg = ad7682_cfg << 2;
	BSP_AD7682_StartCONV();
	BSP_AD7682_Get( ad7682_cfg , &bsp_ad7682_rec[bsp_ad7682_cur_ad_ch]);
}

//void BSP_AD7682_GetValue(void)
//{   
//	BSP_AD7682_StopCONV();
//		
//	bsp_ad7682_data[bsp_ad7982_cur_ad_index ++ ] = bsp_ad7682_rec[bsp_ad7682_cur_ad_ch];
//	if(bsp_ad7982_cur_ad_index == BSP_AD7682_SAMPLE_ADCH * BSP_AD7682_SAMPLEPOINTS)	
//	{

//		bsp_ad7682_CurrentAD7682DataCounter = 0;
//		bsp_ad7682_datareadyprocess = 1;
//		
//		//Dataprocess_Task_Event_Start(DATAPEOCESS_TASK_FILTER_EVENT, EVENT_FROM_ISR);
//	}
//	else if(bsp_ad7982_cur_ad_index >= BSP_AD7682_SAMPLE_ADCH * BSP_AD7682_SAMPLEPOINTS * 2)
//	{
//		bsp_ad7982_cur_ad_index = 0;			
//		bsp_ad7682_CurrentAD7682DataCounter = BSP_AD7682_SAMPLE_ADCH * BSP_AD7682_SAMPLEPOINTS;
//		bsp_ad7682_datareadyprocess = 1;
//		//Dataprocess_Task_Event_Start(DATAPEOCESS_TASK_FILTER_EVENT, EVENT_FROM_ISR);
//	}

//	bsp_ad7682_cur_ad_ch ++;
//	bsp_ad7682_cur_ad_ch = bsp_ad7682_cur_ad_ch % BSP_AD7682_SAMPLE_ADCH;
//	if(((bsp_ad7982_cur_ad_index - bsp_ad7682_cur_ad_ch) % BSP_AD7682_SAMPLE_ADCH)!=0)  //串包的话，这包丢掉
//	{
//		bsp_ad7682_cur_ad_ch = 0;
//		bsp_ad7982_cur_ad_index = 0;
//	} 
//}
void BSP_AD7682_CheckFilterStatus(void)
{
	if(bsp_ad7682_datareadyprocess == 1)
	{
		//Dataprocess_Task_Event_Start(DATAPEOCESS_TASK_FILTER_EVENT, EVENT_FROM_ISR);
		bsp_ad7682_datareadyprocess = 0;
	}
}

void BSP_AD7682_ClearData(void)
{
	bsp_ad7982_cur_ad_index = 0;
	bsp_ad7682_cur_ad_ch = 0;
	bsp_ad7682_CurrentAD7682DataCounter = 0;
	bsp_ad7682_datareadyprocess = 0 ;
}


uint16_t BSP_AD7682_Getcurvalue(uint8_t channel)
{
	return bsp_ad7682_rec[channel];
}
	
//uint16_t * BSP_AD7682_GetDataBuf_Ptr(void)
//{
//	return &bsp_ad7682_data[bsp_ad7682_CurrentAD7682DataCounter];
//}
uint8_t BSP_AD7682_GetRealCH(uint8_t location)
{
	return bsp_ad7682_ch_data_queue[location];
}

// --------------TestFunc ----------------
void BSP_AD7682_TestFunc(void)
{
	
	
	DEBUG("curr_get:%d , real_get:%d\r\n" , bsp_ad7682_getcmd_queue.curr_get,\
											bsp_ad7682_getcmd_queue.real_get);
	
	
	
	DEBUG("IN0:%d,IN1:%d,IN2:%d,IN3:%d\r\n",BSP_AD7682_Value.In_0,BSP_AD7682_Value.In_1,BSP_AD7682_Value.In_2,BSP_AD7682_Value.In_3);
	
}


// ---------------------------------------
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

