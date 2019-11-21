/**
 **************************************************************************************************
 * @file        version.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _VERSION_H_
#define _VERSION_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    version_Modules 
 * @{  
 */

/**
 * @defgroup      version_Exported_Macros 
 * @{  
 */
#define PUBLIC_VERSION_MAJOR        1
#define PUBLIC_VERSION_MINOR        0
#define PUBLIC_VERSION_REVISION     1
#define PUBLIC_VERSION_BUILD        0

#define PRIVATE_VERSION_MAJOR       1   /*!< bit15-12,0-15*/
#define PRIVATE_VERSION_MINOR       0   /*!< bit11-6, 0-63 */
#define PRIVATE_VERSION_REVISION    1   /*!< bit5-0, 0-63 */
/**
 * @}
 */

/**
 * @defgroup      version_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Exported_Types 
 * @{  
 */
typedef struct
{
    uint8_t     PublicMajor;
    uint8_t     PublicMinor;
    uint16_t    PublicRevison;
    uint16_t    PublicBuild;

    uint8_t     PrivateMajor;
    uint8_t     PrivateMinor;
    uint16_t    PrivateRevison;

    uint16_t    BuildYear;
    uint8_t     BuildMonth;
    uint8_t     BuildDay;
    uint8_t     BuildHour;
    uint8_t     BuildMinute;
    uint8_t     BuildSecond;
}Version;
/**
 * @}
 */

/**
 * @defgroup      version_Exported_Variables 
 * @{  
 */
extern const Version g_Version;
/**
 * @}
 */

/**
 * @defgroup      version_Exported_Functions 
 * @{  
 */
void        Version_PublicToString(char* str);
void        Version_PrivateToString(char* str);
uint16_t    Version_GetPrivateStamp(void);

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
