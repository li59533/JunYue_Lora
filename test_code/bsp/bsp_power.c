/**
 **************************************************************************************************
 * @file        bsp_power.c
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
#include "bsp_power.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_e32.h"
#include "bsp_clock.h"
#include "bsp_uart.h"
#include "bsp_systick.h"
#include "bsp_adc.h"

/**
 * @addtogroup    bsp_power_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_power_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_power_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_power_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_power_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_power_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_power_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_power_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_power_Functions 
 * @brief         
 * @{  
 */

typedef enum
{
	Power_Mode_Normal = 0,
	Power_Mode_STOP	  ,
}BSP_Power_Mode_e;


void BSP_Power_SetMode(BSP_Power_Mode_e mode)
{
	DEBUG("Current Mode:%X\r\n" , SMC_GetPowerModeState( SMC ));
}


void BSP_Power_Init(void)
{
	gpio_pin_config_t gpio_pin_config;
	CLOCK_EnableClock(kCLOCK_PortC);
	
	PORT_SetPinMux(PORTC, 3, kPORT_MuxAsGpio);
	gpio_pin_config.pinDirection = kGPIO_DigitalOutput;
	gpio_pin_config.outputLogic = 0;
	GPIO_PinInit(GPIOC, 3, &gpio_pin_config);	
	GPIO_WritePinOutput(GPIOC, 3 , 0);
}

void BSP_Power_EnterVLPS(void)
{
	DEBUG("ENTER VLPS\r\n");
//	APP_GetData_DeInit();
//	BSP_E32_Close();
	BSP_SysTick_DisableIRQ();
	
	BOARD_RUNClockToVLPS();
	
	BSP_SysTick_Init();
//	BSP_E32_Open();
//	APP_GetData_Init();

}


void BSP_Power_EnterVLPS_WithCall(void (* beforefunc)(void) , void (* afterfunc)(void))  
{
	beforefunc();
	BSP_SysTick_DisableIRQ();
	BOARD_RUNClockToVLPS();
	BSP_SysTick_Init();
	afterfunc();
}


void BSP_Power_V30_ON(void)
{
	GPIO_WritePinOutput(GPIOC, 3 , 1);
	DEBUG("V3.0 is ON\r\n");
}

void BSP_Power_V30_OFF(void)
{
	GPIO_WritePinOutput(GPIOC, 3 , 0);
	DEBUG("V3.0 is OFF\r\n");
}

// -------Test Func--------
void BSP_Power_ModeTest(void)
{
}

// ------------------------

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

