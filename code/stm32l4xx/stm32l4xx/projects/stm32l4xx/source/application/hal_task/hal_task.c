/**
 **************************************************************************************************
 * @file        hal_task.c
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
#include "timers.h"
#include "stm32_bsp_conf.h"
#include "system_param.h"
#include "bsp_led.h"
#include "app_power.h"
#include "hal_task.h"
/**
 * @addtogroup    hal_task_Modules 
 * @{  
 */

/**
 * @defgroup      hal_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      hal_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      hal_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t hal_task_tim;
TaskHandle_t  Hal_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      hal_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void hal_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      hal_task_Functions 
 * @brief         
 * @{  
 */

uint32_t Hal_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Hal_Task,\
							"hal Task",\
							1024,
							NULL,
							3,
							&Hal_Task_Handle);
	return basetype;
}


void Hal_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	
	DEBUG("hal Task Enter\r\n");
	UBaseType_t haltask_ramainheap = 0;

	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & HAL_TASK_STANDBY_EVENT) != 0x00)
		{
			DEBUG("HAL_TASK_STANDBY_EVENT\r\n");
			APP_Power_EnterStandbyMode(30);
		}
		
	}
	
}


void Hal_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Hal_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Hal_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}




void Hal_Task_Tim_Init(void)
{
	hal_task_tim = xTimerCreate(	"HalTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									hal_task_tim_callback );
}

void Hal_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( hal_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( hal_task_tim,0);
}
static void hal_task_tim_callback(TimerHandle_t xTimer)
{
	//Hal_Task_Event_Start(Hal_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
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

