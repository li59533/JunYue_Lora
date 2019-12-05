/**
 **************************************************************************************************
 * @file        temperature_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "temperature_task.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32_bsp_conf.h"
#include "system_param.h"
#include "bsp_lmt01.h"
/**
 * @addtogroup    temperature_task_Modules 
 * @{  
 */

/**
 * @defgroup      temperature_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      temperature_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      temperature_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      temperature_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      temperature_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      temperature_task_Public_Variables 
 * @brief         
 * @{  
 */
TaskHandle_t  Temperature_Task_Handle = NULL;
/**
 * @}
 */

/**
 * @defgroup      temperature_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      temperature_task_Functions 
 * @brief         
 * @{  
 */


uint32_t Temperature_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Temperature_Task,\
							"Temperature_Task",\
							512,
							NULL,
							4,
							&Temperature_Task_Handle);
	return basetype;
}

void Temperature_Task(void * pvParameter)
{
	char str_temp[30] ;
	BSP_LMT01_Init();
	DEBUG("Temperature Task Enter\r\n");
	while(1)
	{
		//DEBUG("Temperature Task Looping\r\n");
		BSP_LMT01_StartGetValue();
		vTaskDelay(pdMS_TO_TICKS(500));
		//snprintf(str_temp,30,"%0.3f",g_SystemParam_Param.pdate);
		//DEBUG("Temperature:%s\r\n",str_temp);
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

