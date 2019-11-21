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
#include "first_task.h"

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

/**
 * @}
 */

/**
 * @defgroup      first_task_Functions 
 * @brief         
 * @{  
 */

void First_Task(void * pvParameter)
{
	DEBUG("First Task Enter\r\n");
	UBaseType_t firsttask_ramainheap = 0;
	while(1)
	{
		DEBUG("First Task Looping\r\n");
		Bsp_LedToggle(BSP_LED_TEST);
        
		firsttask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
        
		DEBUG("First Task ramain heap:%d %%\r\n",firsttask_ramainheap);
        vTaskDelay(pdMS_TO_TICKS(1000));
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

