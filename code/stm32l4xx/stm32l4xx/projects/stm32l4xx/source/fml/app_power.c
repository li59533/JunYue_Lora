/**
 **************************************************************************************************
 * @file        app_power.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_power.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
/**
 * @addtogroup    app_power_Modules 
 * @{  
 */

/**
 * @defgroup      app_power_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_power_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_power_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_power_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_power_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_power_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_power_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_power_Functions 
 * @brief         
 * @{  
 */
// AVCC 3.3 -> PE12   ON 
 
void APP_Power_Init(void)
{
	__HAL_RCC_GPIOE_CLK_ENABLE();
	// -------GPIO init----------
	GPIO_InitTypeDef  GPIO_Init;
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pin = GPIO_PIN_12;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init( GPIOE, &GPIO_Init);
	
	APP_Power_AV3_3_OFF();
}

void APP_Power_AV3_3_ON(void)
{
	DEBUG("APP_Power AV3.3V ON\r\n");
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
}

void APP_Power_AV3_3_OFF(void)
{
	DEBUG("APP_Power AV3.3V ON\r\n");
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
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

