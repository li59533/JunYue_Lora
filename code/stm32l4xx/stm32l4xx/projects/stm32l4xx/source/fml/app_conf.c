/**
 **************************************************************************************************
 * @file        app_conf.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_conf.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "bsp_queue.h"

/**
 * @addtogroup    app_conf_Modules 
 * @{  
 */

/**
 * @defgroup      app_conf_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Functions 
 * @brief         
 * @{  
 */
 

void APP_Conf_TestUart(void)
{
	
}

void APP_Conf_SendBytes(uint8_t *buf , uint16_t len )
{
	BSP_Usart_WriteBytes_DMA(BSP_UART_2 , buf , len);
}

void APP_Conf_RevProcess(void)
{
	uint8_t * buf_ptr = 0;
	uint8_t len = 0;
	if(BSP_Queue_GetCount(BSP_QUEUE_UART2_REV) > 0)
	{
		buf_ptr = BSP_Queue_Dequeue(BSP_QUEUE_UART2_REV, &len);
		
		
		
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

