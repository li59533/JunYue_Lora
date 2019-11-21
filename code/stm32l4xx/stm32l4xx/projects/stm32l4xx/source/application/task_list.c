/**
 **************************************************************************************************
 * @file        task_list.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "task_list.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "FreeRTOS.h"
#include "task.h"

#include "first_task.h"
#include "second_task.h"
/**
 * @addtogroup    task_list_Modules 
 * @{  
 */

/**
 * @defgroup      task_list_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      task_list_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      task_list_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      task_list_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Functions 
 * @brief         
 * @{  
 */
 
void RTOS_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(First_Task,\
							"First Task",\
							1024,
							NULL,
							3,
							(TaskHandle_t *)NULL);

	basetype = xTaskCreate(Second_Task,\
							"Second Task",\
							1024,
							NULL,
							2,
							(TaskHandle_t *)NULL);
	
	
	
	
	if(pdPASS == basetype)
	{
		vTaskStartScheduler();
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

