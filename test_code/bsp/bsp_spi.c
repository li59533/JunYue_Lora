/**
 **************************************************************************************************
 * @file        bsp_spi.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_conf.h"

#include "clog.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_spi.h"
#include "bsp_ad7682.h"
/**
 * @addtogroup    bsp_spi_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_spi_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_spi_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_spi_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_spi_Functions 
 * @brief         
 * @{  
 */
 
/*
PC4 -> CS   ALT2
PC5 -> SCK	ALT2
PC6 -> MOSI	ALT2
PC7 -> MISO	ALT2
*/ 
spi_master_handle_t spi0_handle;
 
void BSP_SPI_Init(uint8_t BSP_SPIx , void * instance)
{
	gpio_pin_config_t gpio_pin_config;
	
	// ---------GPIO Init ----------------------
	CLOCK_EnableClock(kCLOCK_PortC);
	
	PORT_SetPinMux(PORTC, 4, kPORT_MuxAlt2);

	
	PORT_SetPinMux(PORTC, 5, kPORT_MuxAlt2);

	
	PORT_SetPinMux(PORTC, 6, kPORT_MuxAlt2);

	
	PORT_SetPinMux(PORTC, 7, kPORT_MuxAlt2);

	// -----------------------------------------
	CLOCK_EnableClock(kCLOCK_Spi0);	
	
	spi_master_config_t config;
	
	SPI_MasterGetDefaultConfig(&config);	

    config.enableMaster = true ;
    config.enableStopInWaitMode = false;
    config.polarity = kSPI_ClockPolarityActiveHigh;
    config.phase = kSPI_ClockPhaseFirstEdge;
    config.direction = kSPI_MsbFirst;

    config.dataMode = kSPI_16BitMode;

    config.txWatermark = kSPI_TxFifoOneHalfEmpty;
    config.rxWatermark = kSPI_RxFifoOneHalfFull;

    config.pinMode = kSPI_PinModeNormal;
    config.baudRate_Bps = 5000000U;

	SPI_MasterInit(SPI0, &config, CLOCK_GetFreq(kCLOCK_BusClk));

	SPI_EnableFIFO(SPI0, false);

	SPI_Enable(SPI0,  true);

	EnableIRQ(SPI0_IRQn);
	SPI_EnableInterrupts(SPI0 , kSPI_TxEmptyInterruptEnable);	
	
	
}


void BSP_SPI_Write16Bits(uint8_t bsp_spix , uint16_t data)
{
	SPI_EnableInterrupts(SPI0 , kSPI_TxEmptyInterruptEnable);	
	SPI_WriteData(SPI0, data);
	
//	SPI_WriteBlocking(SPI0, uint8_t *buffer, size_t size)
	
}


//void BSP_SPI_Read_IT(uint8_t bsp_spix,uint8_t *buf , uint16_t len)
//{
//	HAL_SPI_Receive_IT(&hspi, buf , len);
//}

void BSP_SPI_Write_IT(uint8_t bsp_spix , uint8_t *buf, uint16_t len)
{
	
}

void BSP_SPI_Write(uint8_t bsp_spix , uint8_t *buf, uint16_t len)
{
	
}

void BSP_SPI_Read_IT(uint8_t bsp_spix,uint8_t *buf , uint16_t len)
{
	
}

void BSP_SPI_WriteAndRead_Byte_IT(uint8_t bsp_spix,uint8_t *tbuf , uint8_t * rbuf)
{
	
}



// --------------IRQ -------------------

//static uint16_t spivalue = 0;
void SPI0_IRQHandler(void)
{
	//DEBUG("SPI0_IRQHandler\r\n");
	if((SPI_GetStatusFlags(SPI0) & kSPI_TxBufferEmptyFlag)== kSPI_TxBufferEmptyFlag)
	{
		BSP_AD7682_GetValue(SPI_ReadData(SPI0));
		SPI_DisableInterrupts(SPI0, kSPI_TxEmptyInterruptEnable);

		//DEBUG("SPI0 : value->%d\r\n" , spivalue);
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

