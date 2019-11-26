/**
 **************************************************************************************************
 * @file        bsp_ad7682.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_AD7682_H_
#define _BSP_AD7682_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "bsp_ad7682_port.h"
/**
 * @addtogroup    bsp_ad7682_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_ad7682_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_ad7682_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_ad7682_Exported_Functions 
 * @{  
 */
void BSP_AD7682_Init(void);
void BSP_AD7682_StartGetValue_InConf(void);
void BSP_AD7682_GetValue(void);
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
