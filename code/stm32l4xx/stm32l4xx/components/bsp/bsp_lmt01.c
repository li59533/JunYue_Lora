/**
 **************************************************************************************************
 * @file        bsp_lmt01.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_lmt01.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "system_param.h"
#include "sort.h"
/**
 * @addtogroup    bsp_lmt01_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_lmt01_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Macros_Defines 
 * @brief         
 * @{  
 */

#define LMT01_POWER_ON	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2,GPIO_PIN_SET)
#define LMT01_POWER_OFF	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2,GPIO_PIN_RESET)


/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
	uint32_t lmt01_pulse_count ;
	uint32_t lmt01_pulse_count_record ;
	uint8_t lmt01_pulse_status;
	uint8_t lmt01_updata_status;
	float lmt01_value;
	
	float lmt01_midbuf[5];
	float lmt01_midvalue ; 
	
}bsp_lmt01_data_t ;




/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Private_Variables 
 * @brief         
 * @{  
 */

static bsp_lmt01_data_t bsp_lmt01_data =
{
	.lmt01_pulse_count = 0,
	.lmt01_pulse_count_record = 0,
	.lmt01_pulse_status = LMT01_Pulse_OFF,
	.lmt01_updata_status = LMT01_Updata_NoUp,
};

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void lmt01_gpio_init(void);
static void lmt01_gpio_deinit(void);
static void bsp_lmt01_entermidbuf(float value);
/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Functions 
 * @brief         
 * @{  
 */


void BSP_LMT01_Power_ON(void)
{
	lmt01_gpio_init();
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);  //外部中断使能
	LMT01_POWER_ON;
}
static void lmt01_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();


	/*Configure GPIO pin : PC5 */
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : PB2 */
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
	//  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

static void lmt01_gpio_deinit(void)
{
	HAL_GPIO_DeInit(GPIOC, GPIO_PIN_5);
	HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);
	__HAL_RCC_GPIOB_CLK_DISABLE();
	__HAL_RCC_GPIOC_CLK_DISABLE();	

}
void BSP_LMT01_Power_OFF(void)
{
	LMT01_POWER_OFF;
	
	lmt01_gpio_deinit();
}

void BSP_LMT01_CoreLoop(void)  //call this func in 20ms
{

	switch(bsp_lmt01_data.lmt01_pulse_status)
	{
		case LMT01_Pulse_ON:
		{

			bsp_lmt01_data.lmt01_pulse_status = LMT01_Pulse_OFF;
		}
		break;
		case LMT01_Pulse_OFF:
		{
			bsp_lmt01_data.lmt01_pulse_status = LMT01_Pulse_Wait;
			bsp_lmt01_data.lmt01_pulse_count_record = bsp_lmt01_data.lmt01_pulse_count;
			bsp_lmt01_data.lmt01_pulse_count  = 0;
			bsp_lmt01_data.lmt01_value = ((float)bsp_lmt01_data.lmt01_pulse_count_record * 0.0625f - 50) + g_SystemParam_Config.tempCompensation*0.1f; //补偿值
			bsp_lmt01_data.lmt01_updata_status = LMT01_Updata_HasUp;	
			if(bsp_lmt01_data.lmt01_value < -48.0f)
			{
				
			}
			else
			{
				bsp_lmt01_entermidbuf(bsp_lmt01_data.lmt01_value);
			}
		}
		break;
		case LMT01_Pulse_Wait:
		{
			
		}
		break;
		default:break;
	}

}

uint8_t BSP_LMT01_GetDataStatus(void)
{
	return bsp_lmt01_data.lmt01_updata_status;
}

float BSP_LMT01_GetValue(void)
{
	bsp_lmt01_data.lmt01_updata_status = LMT01_Updata_NoUp;
	return bsp_lmt01_data.lmt01_value;
}


static void bsp_lmt01_entermidbuf(float value)
{
	static uint8_t enter_ptr = 0;
	bsp_lmt01_data.lmt01_midbuf[enter_ptr] = value ;  
	enter_ptr ++ ;
	
	if(enter_ptr ==5)
	{
		enter_ptr = 0;
	}
}
float BSP_LMT01_GetMidValue(void)
{
	float midbuf[5] ;
	bsp_lmt01_data.lmt01_updata_status = LMT01_Updata_NoUp;
	for(uint8_t i = 0 ; i < 5 ; i ++)
	{
		midbuf[i] = bsp_lmt01_data.lmt01_midbuf[i];
	}
	
	Bubble_sort(midbuf , 5);
	
	
	return midbuf[2];
	
}


// -------------------IRQ-------------


void BSP_LMT01_EXTI_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
	bsp_lmt01_data.lmt01_pulse_count ++;
	bsp_lmt01_data.lmt01_pulse_status = LMT01_Pulse_ON;	
	
}





// ------------------Test ------------

void BSP_LMT01_TestFunc(void)
{
	if(BSP_LMT01_GetDataStatus() == LMT01_Updata_HasUp)
	{
		char test_c[50] = { 0 };
		
		sprintf(test_c , "LMT01:%f,PulseCount:%d\r\n" ,bsp_lmt01_data.lmt01_value ,bsp_lmt01_data.lmt01_pulse_count_record);
		DEBUG("%s" , test_c);
	}
	else
	{
		DEBUG("LMT01 Value is NoUp\r\n");
	}
}

// -----------------------------------








/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

