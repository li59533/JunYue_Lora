/**
 **************************************************************************************************
 * @file        app_conf.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_CONF_H_
#define _APP_CONF_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_conf_Modules 
 * @{  
 */

/**
 * @defgroup      app_conf_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Exported_Functions 
 * @{  
 */
 
void APP_Conf_RevProcess(void); 
void APP_Conf_SendBytes(uint8_t *buf , uint16_t len );
void APP_Conf_TestUart(void);
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
