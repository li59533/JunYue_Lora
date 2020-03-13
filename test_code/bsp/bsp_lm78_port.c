/**
 **************************************************************************************************
 * @file        bsp_lm78_port.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_conf.h"
#include "bsp_lm78_port.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_uart.h"
/**
 * @addtogroup    bsp_lm78_port_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_lm78_port_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_port_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_port_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_port_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_port_Private_Variables 
 * @brief         
 * @{  
 */


/**
 * @}
 */
 
/**
 * @defgroup      bsp_lm78_port_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lm78_port_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**s
 * @}
 */


/**
 * @defgroup      bsp_lm78_port_Functions 
 * @brief         
 * @{  
 */
void BSP_LM78_Port_Init(void)
{
	BSP_UART_Init( BSP_UART0);
	BSP_UART_SetBaudRate(BSP_UART0 , 9600);
}

void BSP_LM78_SendBytes(uint8_t * buf, uint16_t len )
{
	BSP_UART_WriteBytes_DMA(BSP_UART0 , buf, len);
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

