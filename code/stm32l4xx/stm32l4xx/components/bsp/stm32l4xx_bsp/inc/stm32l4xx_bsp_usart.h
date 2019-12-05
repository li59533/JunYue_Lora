/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_usart.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _stm32l4xx_bsp_usart_H_
#define _stm32l4xx_bsp_usart_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32l4xx_bsp_usart_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Exported_Macros 
 * @{  
 */
#define BSP_USART1_TX_SIZE          300
#define BSP_USART1_RX_SIZE          300

    // -----DMA Conf Def ------
#define BSP_USART1_DMATX_ENABLE       1
#define BSP_USART1_DMARX_ENABLE       1
    // ------------------------

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_usart_Exported_Types 
 * @{  
 */
typedef struct 
{
    BSP_GPIO_Instance_t GPIO_Instance;
    USART_HandleTypeDef USART_Handle;
    /* data */
}BSP_Usart_Instance_t;
/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Exported_Variables 
 * @{  
 */
extern BSP_Usart_Instance_t BSP_Usart1 ;
/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Exported_Functions 
 * @{  
 */
void BSP_Usart_Init(BSP_Usart_Instance_t * BSP_Usart_Instance);
void BSP_Usart_WriteBytes_Common(BSP_Usart_Instance_t * BSP_Usart_Instance , uint8_t * buf , uint16_t len); // blocking mode
void BSP_Usart_RevOneByteIT_Conf(BSP_Usart_Instance_t * BSP_Usart_Instance);
void BSP_Usart1_IRQHandler(void);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif
