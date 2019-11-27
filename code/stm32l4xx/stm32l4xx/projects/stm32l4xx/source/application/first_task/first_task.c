/**
 **************************************************************************************************
 * @file        first_task.c
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
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32_bsp_conf.h"
#include "system_param.h"
#include "bsp_led.h"
#include "bsp_ad7682.h"
#include "app_power.h"
#include "first_task.h"
/**
 * @addtogroup    first_task_Modules 
 * @{  
 */

/**
 * @defgroup      first_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      first_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      first_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      first_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      first_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      first_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      first_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
TaskHandle_t  First_Task_Handle = NULL;
 
/**
 * @}
 */

/**
 * @defgroup      first_task_Functions 
 * @brief         
 * @{  
 */

uint32_t First_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(First_Task,\
							"First Task",\
							1024,
							NULL,
							3,
							&First_Task_Handle);
	return basetype;
}


void First_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	
	DEBUG("First Task Enter\r\n");
	UBaseType_t firsttask_ramainheap = 0;
//	BSP_Flash_Test();
//	APP_Power_AV3_3_ON();
//	BSP_AD7682_Init();
//	BSP_AD7682_StartSample();
	
	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & FIRST_TASK_TEST_EVENT) != 0x00)
		{
			DEBUG("First Task Looping\r\n");
			firsttask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("First Task ramain heap:%d %%\r\n",firsttask_ramainheap);
			Bsp_LedToggle(BSP_LED_TEST);
			//vTaskDelay(pdMS_TO_TICKS(10000));			
		}
		if((event_flag & FIRST_TASK_TEST2_EVENT) != 0x00)
		{
			DEBUG("First Task FIRST_TASK_TEST2_EVENT\r\n");
			
		}		
		
		
	}
	
}


void First_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(First_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(First_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
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

