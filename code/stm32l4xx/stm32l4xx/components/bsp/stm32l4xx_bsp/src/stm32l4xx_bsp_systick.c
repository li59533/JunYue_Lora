/**
 **************************************************************************************************
 * @file        stm32l4xx_bsp_systick.c
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

/**
 * @addtogroup    stm32l4xx_bsp_systick_Modules 
 * @{  
 */

/**
 * @defgroup      stm32l4xx_bsp_systick_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_systick_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_systick_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_systick_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_systick_Private_Variables 
 * @brief         
 * @{  
 */
TIM_HandleTypeDef        htim8; 
/**
 * @}
 */
 
/**
 * @defgroup      stm32l4xx_bsp_systick_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_systick_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32l4xx_bsp_systick_Functions 
 * @brief         
 * @{  
 */
void BSP_Systick_Init(void) // if using ths HAL ,please using the HAl_Init();
{
	HAL_Init();
}

void BSP_Systick_Delayms(uint32_t delay) // block delay
{
	HAL_Delay(delay);
}

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  RCC_ClkInitTypeDef    clkconfig;
  uint32_t              uwTimclock = 0;
  uint32_t              uwPrescalerValue = 0;
  uint32_t              pFLatency;
  
  /*Configure the TIM8 IRQ priority */
  HAL_NVIC_SetPriority(TIM8_UP_IRQn, TickPriority ,0); 
  
  /* Enable the TIM8 global Interrupt */
  HAL_NVIC_EnableIRQ(TIM8_UP_IRQn); 
  
  /* Enable TIM8 clock */
  __HAL_RCC_TIM8_CLK_ENABLE();
  
  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  
  /* Compute TIM8 clock */
  uwTimclock = HAL_RCC_GetPCLK2Freq();
   
  /* Compute the prescaler value to have TIM8 counter clock equal to 1MHz */
  uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000) - 1);
  
  /* Initialize TIM8 */
  htim8.Instance = TIM8;
  
  /* Initialize TIMx peripheral as follow:
  + Period = [(TIM8CLK/1000) - 1]. to have a (1/1000) s time base.
  + Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
  + ClockDivision = 0
  + Counter direction = Up
  */
  htim8.Init.Period = (1000000 / 1000) - 1;
  htim8.Init.Prescaler = uwPrescalerValue;
  htim8.Init.ClockDivision = 0;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_Base_Init(&htim8) == HAL_OK)
  {
    /* Start the TIM time Base generation in interrupt mode */
    return HAL_TIM_Base_Start_IT(&htim8);
  }
  
  /* Return function status */
  return HAL_ERROR;
}
void HAL_SuspendTick(void)
{
  /* Disable TIM8 update Interrupt */
  __HAL_TIM_DISABLE_IT(&htim8, TIM_IT_UPDATE);                                                  
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling TIM8 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_ResumeTick(void)
{
  /* Enable TIM8 Update interrupt */
  __HAL_TIM_ENABLE_IT(&htim8, TIM_IT_UPDATE);
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

