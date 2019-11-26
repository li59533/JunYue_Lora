/**
 **************************************************************************************************
 * @file        dataprocess_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "dataprocess_task.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "FreeRTOS.h"
#include "task.h"
#include "clog.h"
/**
 * @addtogroup    dataprocess_task_Modules 
 * @{  
 */

/**
 * @defgroup      dataprocess_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dataprocess_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dataprocess_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      dataprocess_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      dataprocess_task_Functions 
 * @brief         
 * @{  
 */
 
void DataProcess_Task(void * pvParameter)
{

	while(1)
	{
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

