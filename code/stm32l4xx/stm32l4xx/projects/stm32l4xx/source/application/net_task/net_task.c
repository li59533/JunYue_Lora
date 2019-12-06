/**
 **************************************************************************************************
 * @file        net_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "limits.h"
#include "net_task.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32_bsp_conf.h"
#include "system_param.h"
#include "rtos_tools.h"

#include "app_power.h"
#include "bsp_lm78.h"
#include "bsp_led.h"
#include "timers.h"
/**
 * @addtogroup    net_task_Modules 
 * @{  
 */

/**
 * @defgroup      net_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      net_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      net_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      net_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      net_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t net_task_timout;
/**
 * @}
 */
 
/**
 * @defgroup      net_task_Public_Variables 
 * @brief         
 * @{  
 */
TaskHandle_t  Net_Task_Handle = NULL;
/**
 * @}
 */

/**
 * @defgroup      net_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void net_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      net_task_Functions 
 * @brief         
 * @{  
 */


uint32_t Net_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Net_Task,\
							"Net_Task",\
							1024,
							NULL,
							2,
							&Net_Task_Handle);
	NET_Task_Tim_Init();
	return basetype;
}


void float_test(void)
{
	float some_flaot = 56.3f;
	uint8_t buf[4] = { 0 };
	float battery = 0.0f;
	memcpy(buf, (uint8_t *)& some_flaot , 4);
	battery = * (float *)buf;
	battery = battery + 0.01f;
}





void Net_Task(void * pvParameter)
{
	uint32_t event_flag = 0;	
	DEBUG("Net Task Enter\r\n");
	APP_Power_LM78_ON();
	BSP_LM78_Init();
	//NET_Task_Tim_Init();
	//NET_Task_StartTim(10000);
	
	Net_Task_Event_Start(NET_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
	
	while(1)
	{
		DEBUG("Net Task Looping\r\n");
		Bsp_LedToggle(BSP_LED_TEST);
		
		/*
		char test_lorabuf[] = "\r\nAT+SENDB=2:FF\r\n";
		BSP_LM78_SendBytes((uint8_t *)test_lorabuf,sizeof(test_lorabuf));
		DEBUG("test_lorabuf_Size:%d\r\n",sizeof(test_lorabuf));
//		BSP_LM78_SendBytes((uint8_t *)test_lorabuf,sizeof(test_lorabuf));
		vTaskDelay(pdMS_TO_TICKS(30000));
		*/
		
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
	
		if((event_flag & NET_TASK_SEND_AT_EVENT) != 0x00)
		{	
			BSP_LM78_ReqProcess();
			DEBUG("NET_TASK_SEND_AT_EVENT\r\n");
		}
		
		if((event_flag & NET_TASK_AT_PROCESS_EVENT) != 0x00)
		{
			BSP_LM78_RespProcess();
			DEBUG("NET_TASK_AT_PROCESS_EVENT\r\n");
		}	
		
	}
	
}
	

void Net_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	BaseType_t HigherPriorityTaskWoken = pdFALSE;
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Net_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Net_Task_Handle, events, eSetBits , &HigherPriorityTaskWoken);
		}
		break;
		default:break;
	}
}
		


void NET_Task_Tim_Init(void)
{
	net_task_timout = xTimerCreate(	"NetTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									net_task_tim_callback );
}

void NET_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( net_task_timout,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( net_task_timout,0);
}
static void net_task_tim_callback(TimerHandle_t xTimer)
{
	Net_Task_Event_Start(NET_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
}


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

