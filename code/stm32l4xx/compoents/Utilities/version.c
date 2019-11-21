/**
 **************************************************************************************************
 * @file        version.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stdint.h"
#include "stdio.h"
#include "version.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    version_Modules 
 * @{  
 */

/**
 * @defgroup      version_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Public_Variables 
 * @brief         
 * @{  
 */
const Version g_Version =
{
    .PublicMajor = PUBLIC_VERSION_MAJOR,
    .PublicMinor = PUBLIC_VERSION_MINOR,
    .PublicRevison = PUBLIC_VERSION_REVISION,
    .PublicBuild = PUBLIC_VERSION_BUILD,
    .PrivateMajor = PRIVATE_VERSION_MAJOR,
    .PrivateMinor = PRIVATE_VERSION_MINOR,
    .PrivateRevison = PRIVATE_VERSION_REVISION,
};
/**
 * @}
 */

/**
 * @defgroup      version_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Functions 
 * @brief         
 * @{  
 */


void Version_PublicToString(char* str)
{
    sprintf(str,"%d.%d.%d",g_Version.PublicMajor,g_Version.PublicMinor,g_Version.PublicRevison);
}

void Version_PrivateToString(char* str)
{
    sprintf(str,"%d.%d.%d",g_Version.PrivateMajor,g_Version.PrivateMinor,g_Version.PrivateRevison);
}

uint16_t Version_GetPrivateStamp(void)
{
    return (uint16_t)((PRIVATE_VERSION_MAJOR<<12) | (PRIVATE_VERSION_MINOR<<6) | (PRIVATE_VERSION_REVISION));
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

