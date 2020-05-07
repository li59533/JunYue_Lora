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
static uint8_t bsp_usart2_tx[BSP_USART2_TX_SIZE] = { 0 };
static uint8_t bsp_usart2_rx[BSP_USART2_RX_SIZE] = { 0 };
// ------------------------

static uint8_t bsp_usart1_rxtemp = 0;
static uint8_t bsp_usart2_rxtemp = 0;


static uint16_t usart1_i = 0;
static uint16_t usart2_i = 0;

UART_HandleTypeDef husart1 ;
DMA_HandleTypeDef hdma ; 


UART_HandleTypeDef husart2 ;
DMA_HandleTypeDef husart2_dma_t;
DMA_HandleTypeDef husart2_dma_r;

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




void BSP_Usart_Init(uint8_t  BSP_Uart_X)
{
	if(BSP_Uart_X == BSP_UART_1)
	{
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

//		USART1->CR2 |= 0x01 << 15;
//		husart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_SWAP_INIT; // this is the hardware making RX and TX changed
//		husart1.AdvancedInit.Swap = UART_ADVFEATURE_SWAP_ENABLE;
//		
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

	}
	
	if(BSP_Uart_X == BSP_UART_2)
	{
		husart2.Instance = USART2;
		husart2.Init.BaudRate = 115200;
		husart2.Init.WordLength = UART_WORDLENGTH_8B;
		husart2.Init.StopBits = UART_STOPBITS_1;
		husart2.Init.Parity = UART_PARITY_NONE;
		husart2.Init.Mode = UART_MODE_TX_RX;
		husart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		husart2.Init.OverSampling = UART_OVERSAMPLING_16;
		husart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
		husart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
		husart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;	


//		husart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_SWAP_INIT;
//		husart2.AdvancedInit.Swap = UART_ADVFEATURE_SWAP_ENABLE;
		if (HAL_UART_Init(&husart2) != HAL_OK)
		{
		DEBUG("Hal_Usart Init Err\r\n");
		}
		if (HAL_UARTEx_SetTxFifoThreshold(&husart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
		{
		DEBUG("Hal_Usart Init Err\r\n");
		}
		if (HAL_UARTEx_SetRxFifoThreshold(&husart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
		{
		DEBUG("Hal_Usart Init Err\r\n");
		}
		if (HAL_UARTEx_DisableFifoMode(&husart2) != HAL_OK)
		{
		DEBUG("Hal_Usart Init Err\r\n");
		}

	}
	
	
}



void BSP_Usart_RevOneByteIT_Conf(uint8_t  BSP_Uart_X)  // IT in rev 1 byte
{
	
	if( BSP_Uart_X == BSP_UART_1)
	{
		HAL_UART_Receive_IT( &husart1 , &bsp_usart1_rxtemp, 1);
	}
	if( BSP_Uart_X == BSP_UART_2)
	{
		HAL_UART_Receive_IT( &husart2 , &bsp_usart2_rxtemp, 1);
	}	
	
}


void BSP_Usart_WriteBytes_Common(uint8_t  BSP_Uart_X , uint8_t * buf , uint16_t len) // blocking mode
{
	switch(BSP_Uart_X)
	{
		case BSP_UART_1:HAL_UART_Transmit(&husart1, buf , len , 1000);break;
		case BSP_UART_2:HAL_UART_Transmit(&husart2, buf , len , 1000);break;
		default:break;
	}
	
}

void BSP_Usart_WriteBytes_DMA(uint8_t  BSP_Uart_X , uint8_t * buf , uint16_t len)
{
	switch(BSP_Uart_X)
	{
		case BSP_UART_1:HAL_UART_Transmit_DMA( &husart1, buf, len);break;
		case BSP_UART_2:HAL_UART_Transmit_DMA( &husart2, buf, len);break;
		default:break;
	}	
	
	
	
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
	
    if(huart->Instance == USART2)
    {
        // ----- CLK Enbale -----
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		__HAL_RCC_USART2_CLK_ENABLE();
        // ----------------------
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		
		// --------DMA Conf------------------
		__HAL_RCC_DMAMUX1_CLK_ENABLE();
		__HAL_RCC_DMA1_CLK_ENABLE();
		
		husart2_dma_t.Instance = DMA1_Channel2 ;
		husart2_dma_t.Init.Direction = DMA_MEMORY_TO_PERIPH;
		husart2_dma_t.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		husart2_dma_t.Init.MemInc = DMA_MINC_ENABLE;
		husart2_dma_t.Init.Mode = DMA_NORMAL;
		husart2_dma_t.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		husart2_dma_t.Init.PeriphInc = DMA_PINC_DISABLE;
		husart2_dma_t.Init.Priority = DMA_PRIORITY_MEDIUM;
		husart2_dma_t.Init.Request = DMA_REQUEST_USART2_TX;
		HAL_DMA_Init(&husart2_dma_t);
		
		HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 4, 0);
		HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
		
		__HAL_LINKDMA(huart,hdmatx,husart2_dma_t);
		
		// ----------------------------------
		
		// --------NVIC configuration--------
		__HAL_UART_ENABLE_IT( &husart2, UART_IT_IDLE); 
		__HAL_UART_CLEAR_IDLEFLAG(&husart2);
		HAL_NVIC_SetPriority(USART2_IRQn, 7, 0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
		// ----------------------------------
		
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PB7     ------> USART1_RX
    PB6     ------> USART1_TX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7|GPIO_PIN_6);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(huart->hdmatx);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA15 (JTDI)     ------> USART2_RX
    PD5     ------> USART2_TX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_5);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }

}

// -----------------------------------------------------


// ------------------USART1_IRQHandler------------------
void BSP_Usart1_IRQHandler(void)
{
	

	if(__HAL_UART_GET_IT(&husart1, UART_IT_IDLE) == SET)
	{
		BSP_Queue_Enqueue( BSP_QUEUE_UART1_REV , bsp_usart1_rx , usart1_i);
		memset(bsp_usart1_rx , 0 , sizeof(bsp_usart1_rx));
		usart1_i = 0;
		__HAL_UART_CLEAR_IDLEFLAG(&husart1);
		DEBUG("ENTER Uart1 IDLE \r\n");
	}
	HAL_UART_IRQHandler( &husart1);
	__HAL_UART_CLEAR_OREFLAG(&husart1);
	
}

// ------------------USART2_IRQHandler------------------
void BSP_Usart2_IRQHandler(void)
{

	if(__HAL_UART_GET_IT(&husart2, UART_IT_IDLE) == SET)
	{
		BSP_Queue_Enqueue( BSP_QUEUE_UART2_REV , bsp_usart2_rx , usart2_i);
		memset(bsp_usart2_rx , 0 , sizeof(bsp_usart2_rx));
		usart2_i = 0;
		__HAL_UART_CLEAR_IDLEFLAG(&husart2);
		DEBUG("ENTER Uart2 IDLE \r\n");
	}
	
	HAL_UART_IRQHandler( &husart2);
	__HAL_UART_CLEAR_OREFLAG(&husart2);
	
	
	
}
 // ----------------------------------------------------

void BSP_UART1_DMA1_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma);
}

void BSP_UART2_DMA1_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&husart2_dma_t);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		bsp_usart1_rx[usart1_i] = bsp_usart1_rxtemp;	
		usart1_i ++;
		if(usart1_i >= BSP_USART1_RX_SIZE)
		{
			usart1_i = 0;
		}
		HAL_UART_Receive_IT( &husart1 ,  &bsp_usart1_rxtemp, 1);
	}

	if(huart->Instance == USART2)
	{
		
		bsp_usart2_rx[usart2_i] = bsp_usart2_rxtemp;
		usart2_i ++;
		if(usart2_i >= BSP_USART2_RX_SIZE)
		{
			usart2_i = 0;
		}
		HAL_UART_Receive_IT( &husart2 , &bsp_usart2_rxtemp, 1);
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

