/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_flash.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stm32l4xx_bsp_conf.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
/**
 * @addtogroup    stm32l4xx_bsp_flash_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_flash_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_flash_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_flash_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_flash_Functions 
 * @brief         
 * @{  
 */


HAL_StatusTypeDef BSP_Flash_WriteBytes(uint32_t addr_start,uint8_t * buf,uint16_t len)
{
	FLASH_EraseInitTypeDef pEraseInit = { 0 };
	uint32_t PageError = 0;
	uint16_t start_offset = 0;
	uint16_t page_lostspace = 0;
	HAL_StatusTypeDef hal_status ;
	
	uint32_t addr_offset = 0;
	addr_offset = addr_start - BSP_FLASH_HEAD_ADDR;
	pEraseInit.Page = addr_offset / BSP_FLASH_SECTOR_SIZE;
	start_offset = addr_offset % BSP_FLASH_SECTOR_SIZE;
	start_offset = 1044480 % 2048;
	DEBUG("start_offset:%d\r\n",start_offset);
	page_lostspace = BSP_FLASH_SECTOR_SIZE - start_offset;
	
	if(page_lostspace > len )
	{
		pEraseInit.NbPages = 1;
	}
	else
	{
		if(((len - page_lostspace) / BSP_FLASH_SECTOR_SIZE) == 0)
		{
			pEraseInit.NbPages = (len - page_lostspace) / BSP_FLASH_SECTOR_SIZE;
		}
		else
		{
			pEraseInit.NbPages = (len - page_lostspace) / BSP_FLASH_SECTOR_SIZE +1;
		}	
	}
	pEraseInit.Banks = FLASH_BANK_BOTH;
	
	pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;

	HAL_FLASH_Unlock();
	
	hal_status = HAL_FLASHEx_Erase( &pEraseInit, &PageError);
	while(__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) == SET)
	{
		DEBUG("Flash is busy\r\n");
	}	
	for(uint16_t i = 0; i < len; i += 8)
	{
		hal_status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,addr_start, *(uint64_t *)(buf + i));
		addr_start += 2;
	}
	while(__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) == SET)
	{
		DEBUG("Flash is busy\r\n");
	}
	HAL_FLASH_Lock();
	return hal_status;
}

uint16_t BSP_Flash_ReadBytes(uint8_t *buf,uint32_t addr,uint16_t len)
{
	uint8_t * read_ptr = (uint8_t *)addr;
	for(uint16_t i = 0; i < len; i ++)
	{
		*(buf + i) = *(read_ptr + i);
	}
	return len;
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

