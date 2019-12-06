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
#include "bsp_queue.h"
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

// --- Usart data space ---

static uint8_t bsp_usart1_tx[BSP_USART1_TX_SIZE] = { 0 };
static uint8_t bsp_usart1_rx[BSP_USART1_RX_SIZE] = { 0 };

// ------------------------



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
    .GPIO_Instance.GPIO_Init.Alternate = GPIO_AF7_USART1,
    .USART_Handle.Instance = USART1,
    .USART_Handle.Init.BaudRate = 9600,
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




static uint16_t usart1_i = 0;


UART_HandleTypeDef husart1 ;
DMA_HandleTypeDef hdma ; 
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
   
	husart1.Instance = USART1;
	husart1.Init.BaudRate = 9600;
	husart1.Init.WordLength = UART_WORDLENGTH_8B;
	husart1.Init.StopBits = UART_STOPBITS_1;
	husart1.Init.Parity = UART_PARITY_NONE;
	husart1.Init.Mode = UART_MODE_TX_RX;
	husart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	husart1.Init.OverSampling = UART_OVERSAMPLING_16;
	husart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	husart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	husart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;	

	//USART1->CR2 |= 0x01 << 15;
	husart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_SWAP_INIT;
	husart1.AdvancedInit.Swap = UART_ADVFEATURE_SWAP_ENABLE;
	if (HAL_UART_Init(&husart1) != HAL_OK)
	{
	DEBUG("Hal_Usart Init Err\r\n");
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&husart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
	DEBUG("Hal_Usart Init Err\r\n");
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&husart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
	DEBUG("Hal_Usart Init Err\r\n");
	}
	if (HAL_UARTEx_DisableFifoMode(&husart1) != HAL_OK)
	{
	DEBUG("Hal_Usart Init Err\r\n");
	}
	//MODIFY_REG(husart1.Instance->CR2, USART_CR2_SWAP, UART_ADVFEATURE_SWAP_ENABLE);
	
}



void BSP_Usart_RevOneByteIT_Conf(BSP_Usart_Instance_t * BSP_Usart_Instance)  // IT in rev 1 byte
{
	
	if( BSP_Usart_Instance->USART_Handle.Instance == USART1)
	{
		HAL_UART_Receive_IT( &husart1 , bsp_usart1_rx + usart1_i, 1);
	}
}


void BSP_Usart_WriteBytes_Common(BSP_Usart_Instance_t * BSP_Usart_Instance , uint8_t * buf , uint16_t len) // blocking mode
{
	HAL_UART_Transmit(&husart1, buf , len , 1000);
}

void BSP_Usart_WriteBytes_DMA(BSP_Usart_Instance_t * BSP_Usart_Instance , uint8_t * buf , uint16_t len)
{
	HAL_UART_Transmit_DMA( &husart1, buf, len);
}


// ------------- HAL Will Call This Func ---------------
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    if(huart->Instance == USART1)
    {
        // ----- CLK Enbale -----
        //__HAL_RCC_DMA1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_USART1_CLK_ENABLE();
        // ----------------------
		GPIO_InitTypeDef GPIO_Init;
		GPIO_Init.Alternate = GPIO_AF7_USART1;
		GPIO_Init.Mode = GPIO_MODE_AF_PP;
		GPIO_Init.Pin = GPIO_PIN_9|GPIO_PIN_10;
		GPIO_Init.Pull = GPIO_NOPULL;
		GPIO_Init.Speed = GPIO_SPEED_FAST;
		
		HAL_GPIO_Init(GPIOA , &GPIO_Init);

		
		
		
		// --------DMA Conf------------------
		  __HAL_RCC_DMAMUX1_CLK_ENABLE();
		__HAL_RCC_DMA1_CLK_ENABLE();
		//DMA_HandleTypeDef hdma ; 
		hdma.Instance = DMA1_Channel1 ;
		hdma.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma.Init.MemInc = DMA_MINC_ENABLE;
		hdma.Init.Mode = DMA_NORMAL;
		hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma.Init.Priority = DMA_PRIORITY_MEDIUM;
		hdma.Init.Request = DMA_REQUEST_USART1_TX;
		HAL_DMA_Init(&hdma);
		
		//__HAL_DMA_ENABLE_IT(hdma, DMA_IT_TC) 
		HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 3, 0);
		HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
		
		
		__HAL_LINKDMA(huart,hdmatx,hdma);
		
		// ----------------------------------
		
		// --------NVIC configuration--------
		__HAL_UART_ENABLE_IT( &husart1, UART_IT_IDLE); 
		__HAL_UART_CLEAR_IDLEFLAG(&husart1);
		HAL_NVIC_SetPriority(USART1_IRQn, 7, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		// ----------------------------------
		
    }
    DEBUG("Enter the hal_uart_mspinit\r\n");
}
// -----------------------------------------------------


// ------------------USART1_IRQHandler------------------
void BSP_Usart1_IRQHandler(void)
{
	HAL_UART_IRQHandler( &husart1);
	if(__HAL_UART_GET_IT(&husart1, UART_IT_IDLE) == SET)
	{
		BSP_Queue_Enqueue( BSP_QUEUE_UART1_REV , bsp_usart1_rx , usart1_i);
		
		usart1_i = 0;
		__HAL_UART_CLEAR_IDLEFLAG(&husart1);
		DEBUG("ENTER Uart IDLE \r\n");
	}
}

void BSP_DMA1_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	if(huart->Instance == USART1)
	{
		//HAL_UART_Receive_IT( huart , bsp_usart1_rx + usart1_i , 1);
		HAL_UART_Receive_IT( &husart1 , bsp_usart1_rx + usart1_i, 1);
			
		usart1_i ++;
		if(usart1_i >= BSP_USART1_RX_SIZE)
		{
			usart1_i = 0;
		}
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

