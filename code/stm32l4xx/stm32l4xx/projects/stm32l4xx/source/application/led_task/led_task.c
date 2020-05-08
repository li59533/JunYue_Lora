/**
 **************************************************************************************************
 * @file        led_task.c
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
#include "led_task.h" 
#include "clog.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stm32_bsp_conf.h"


/**
 * @addtogroup    led_task_Modules 
 * @{  
 */
 
#include "bsp_led.h"

/**
 * @defgroup      led_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      led_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      led_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      led_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      led_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t led_task_tim;
TaskHandle_t  Led_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      led_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      led_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void led_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      led_task_Functions 
 * @brief         
 * @{  
 */

uint32_t Led_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Led_Task,\
							"Led Task",\
							512,
							NULL,
							3,
							&Led_Task_Handle);
	
	
	
	
	
	
	return basetype;
}


void Led_Task(void * pvParameter)
{
	BSP_LED_BlinkStandard_3(BSP_LED_TEST,Blink_LowSpeed);
	while(1)
	{

		BSP_Led_UpdateStatus();
		vTaskDelay(pdMS_TO_TICKS(5));
	}		
}


void Led_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Led_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Led_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}




void Led_Task_Tim_Init(void)
{
	led_task_tim = xTimerCreate(	"LedTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									led_task_tim_callback );
}

void Led_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( led_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( led_task_tim,0);
}
static void led_task_tim_callback(TimerHandle_t xTimer)
{
	//Led_Task_Event_Start(Led_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
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

