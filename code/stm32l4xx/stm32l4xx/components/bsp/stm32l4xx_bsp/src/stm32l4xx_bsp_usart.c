/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_usart.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "stm32_bsp_conf.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
/**
 * @addtogroup    stm32l4xx_bsp_usart_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_usart_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Private_Types
 * @brief         
 * @{  
 */



/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_usart_Private_Variables 
 * @brief         
 * @{  
 */

static uint8_t bsp_usart1_tx[BSP_USART1_TX_SIZE] = { 0 };
static uint8_t bsp_usart1_rx[BSP_USART1_RX_SIZE] = { 0 };

DMA_HandleTypeDef usart1_dma_tx = 
{
    .Instance = DMA1_Channel4,
   // .Init.Request = DMA_REQUEST_2,
    .Init.Direction = DMA_MEMORY_TO_PERIPH,
    .Init.PeriphInc = DMA_PINC_DISABLE,
    .Init.MemInc = DMA_MINC_ENABLE,
    .Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
    .Init.MemDataAlignment = DMA_MDATAALIGN_BYTE ,
    .Init.Mode = DMA_NORMAL,
    .Init.Priority = DMA_PRIORITY_HIGH,
};
DMA_HandleTypeDef usart1_dma_rx = 
{
    .Instance = DMA1_Channel5,
   // .Init.Request = DMA_REQUEST_2,
    .Init.Direction = DMA_PERIPH_TO_MEMORY,
    .Init.PeriphInc = DMA_PINC_DISABLE,
    .Init.MemInc = DMA_MINC_ENABLE,
    .Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
    .Init.MemDataAlignment = DMA_MDATAALIGN_BYTE ,
    .Init.Mode = DMA_NORMAL,
    .Init.Priority = DMA_PRIORITY_HIGH,
};

BSP_Usart_Instance_t BSP_Usart1 = 
{
	.GPIO_Instance.GPIOx = GPIOA ,
	.GPIO_Instance.GPIO_Init.Pin = GPIO_PIN_9 |GPIO_PIN_10,
    .GPIO_Instance.GPIO_Init.Mode = GPIO_MODE_AF_PP,
    .GPIO_Instance.GPIO_Init.Pull = GPIO_PULLUP,
    .GPIO_Instance.GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
    //.GPIO_Instance.GPIO_Init.Alternate
    .USART_Handle.Instance = USART1,
    .USART_Handle.Init.BaudRate = 115200,
    .USART_Handle.Init.WordLength = USART_WORDLENGTH_8B,
    .USART_Handle.Init.StopBits = USART_STOPBITS_1,
    .USART_Handle.Init.Parity = USART_PARITY_NONE,
    .USART_Handle.Init.Mode = USART_MODE_TX_RX,
    .USART_Handle.Init.CLKPolarity = USART_POLARITY_LOW,
    .USART_Handle.Init.CLKPhase = USART_PHASE_1EDGE,
    .USART_Handle.Init.CLKLastBit = USART_LASTBIT_DISABLE,
    .USART_Handle.pTxBuffPtr = bsp_usart1_tx,
    .USART_Handle.TxXferSize = BSP_USART1_TX_SIZE,
    .USART_Handle.TxXferCount = 0,
    .USART_Handle.pRxBuffPtr = bsp_usart1_rx,
    .USART_Handle.RxXferSize = BSP_USART1_TX_SIZE,
    .USART_Handle.RxXferCount = 0,
    .USART_Handle.hdmatx = &usart1_dma_tx,
    .USART_Handle.hdmarx = &usart1_dma_rx,
};


/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_usart_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_usart_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**s
 * @}
 */


/**
 * @defgroup      stm32l4xx_bsp_usart_Functions 
 * @brief         
 * @{  
 */

void BSP_Usart_Init(BSP_Usart_Instance_t * BSP_Usart_Instance)
{
    //--- RCC Enable --- 
	HAL_GPIO_Init(BSP_Usart_Instance->GPIO_Instance.GPIOx , &BSP_Usart_Instance->GPIO_Instance.GPIO_Init);
    
    if(HAL_USART_Init(&BSP_Usart_Instance->USART_Handle) != HAL_OK)
	{
		DEBUG("Hal_Usart Init Err\r\n");
	}
}


void BSP_Usart_WriteBytes_Common(BSP_Usart_Instance_t * BSP_Usart_Instance , uint8_t * buf , uint16_t len) // blocking mode
{
	HAL_USART_Transmit(&BSP_Usart_Instance->USART_Handle, buf , len , 0);
}





















// ------------- HAL Will Call This Func ---------------
void HAL_UART_MspInit(UART_HandleTypeDef * huart)
{
    if(huart->Instance == USART1)
    {
        // ----- CLK Enbale -----
        __HAL_RCC_DMA1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_USART1_CLK_ENABLE();
        // ----------------------
    }
	
    DEBUG("Enter the hal_uart_mspinit\r\n");
}
// -----------------------------------------------------

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

