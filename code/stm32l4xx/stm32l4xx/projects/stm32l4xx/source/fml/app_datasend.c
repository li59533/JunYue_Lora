/**
 **************************************************************************************************
 * @file        app_datasend.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_datasend.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "bsp_lm78.h"
#include "system_param.h" 
/**
 * @addtogroup    app_datasend_Modules 
 * @{  
 */

/**
 * @defgroup      app_datasend_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datasend_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datasend_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_datasend_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_datasend_Functions 
 * @brief         
 * @{  
 */
 
 
void app_datasend_test(void)
{
	float temp = 5.5;
	uint8_t float_temp[4];
	char buf[30];
	uint8_t ptr = 0;
	memcpy( float_temp, (uint8_t *)&temp , 4 );
	
	for(uint8_t i = 0; i < 4 ; i ++)
	{
		ptr += snprintf(buf + ptr , 30 - ptr , "%02X",float_temp[i]);
	}
	DEBUG("%s\r\n",buf);
}
	

int8_t APP_DataSend_SendCharacteristic(void)
{
	char app_databuf[200] = { 0 };
	uint8_t app_databuf_ptr = 0;
	
	app_datasend_test();
	
	for(uint8_t i = 0 ; i < 3; i ++)
	{
		memcpy(app_databuf + 20*i + 0 , &g_SystemParam_Param.EffectiveValue[i] , 4 );
		memcpy(app_databuf + 20*i + 4, &g_SystemParam_Param.Vrms[i] , 4 );
		memcpy(app_databuf + 20*i + 8, &g_SystemParam_Param.Drms[i] , 4 );
		memcpy(app_databuf + 20*i + 12, &g_SystemParam_Param.KurtosisIndex[i] , 4 );
		memcpy(app_databuf + 20*i + 16, &g_SystemParam_Param.Envelop[i] , 4 );
		
		/*
		app_databuf_ptr += snprintf(app_databuf + app_databuf_ptr, 200 - app_databuf_ptr , "E%0.3fV%0.3fD%0.3fK%0.3fE%0.3f",g_SystemParam_Param.EffectiveValue[i],\
																										g_SystemParam_Param.Vrms[i],\
																										g_SystemParam_Param.Drms[i],\
																										g_SystemParam_Param.KurtosisIndex[i],\
																										g_SystemParam_Param.Envelop[i]);
		*/	
	}
	
	app_databuf_ptr += snprintf(app_databuf + app_databuf_ptr, 200 - app_databuf_ptr ,"T%0.3f", g_SystemParam_Param.pdate);
	DEBUG("This Value will send:%s len:%d\r\n",app_databuf,strlen((const char *)app_databuf));
	
	
	BSP_LM78_StartSend((uint8_t *)app_databuf, strlen((const char *)app_databuf));
	return 0 ; 
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

