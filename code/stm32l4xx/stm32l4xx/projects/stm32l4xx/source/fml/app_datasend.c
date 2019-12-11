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
	char app_datastrbuf[200] = { 0 };
	uint16_t ptr = 0;
	uint8_t app_databuf_ptr = 0;
	uint16_t len = 0 ;
	app_datasend_test();
	struct
	{
		uint16_t EffectiveValue[4];
		uint16_t Vrms[4];
		uint16_t Drms[4];
		uint16_t KurtosisIndex[4];
		uint16_t Envelop[4];
	}character_buf;
	
	
	for( uint8_t i = 0 ; i < 3 ; i ++)
	{
		if(g_SystemParam_Param.EffectiveValue[i] <= 6000.0f)
		{
			character_buf.EffectiveValue[i] = (uint16_t)(g_SystemParam_Param.EffectiveValue[i] * 10);
		}
		else
		{
			character_buf.EffectiveValue[i] = 60000;
		}
		
		if(g_SystemParam_Param.Vrms[i] <= 6000.0f)
		{
			character_buf.Vrms[i] = (uint16_t)(g_SystemParam_Param.Vrms[i] * 10);
		}
		else
		{
			character_buf.Vrms[i] = 60000;
		}
		
		if(g_SystemParam_Param.Drms[i] <= 6000.0f)
		{
			character_buf.Drms[i] = (uint16_t)(g_SystemParam_Param.Drms[i] * 10);
		}
		else
		{
			character_buf.Drms[i] = 60000;
		}

		if(g_SystemParam_Param.KurtosisIndex[i] <= 6000.0f)
		{
			character_buf.KurtosisIndex[i] = (uint16_t)(g_SystemParam_Param.KurtosisIndex[i] * 10);
		}
		else
		{
			character_buf.KurtosisIndex[i] = 60000;
		}
		
		if(g_SystemParam_Param.Envelop[i] <= 6000.0f)
		{
			character_buf.Envelop[i] = (uint16_t)(g_SystemParam_Param.Envelop[i] * 10);
		}
		else
		{
			character_buf.Envelop[i] = 60000;
		}		
	}
	
	
	for(uint8_t i = 0 ; i < 3; i ++)
	{
		memcpy(app_databuf + 10*i + 0 , &character_buf.EffectiveValue[i] , 2 );
		memcpy(app_databuf + 10*i + 2, &character_buf.Vrms[i] , 2 );
		memcpy(app_databuf + 10*i + 4, &character_buf.Drms[i] , 2 );
		memcpy(app_databuf + 10*i + 6, &character_buf.KurtosisIndex[i] , 2 );
		memcpy(app_databuf + 10*i + 8, &character_buf.Envelop[i] , 2 );
		len = 10*i + 8 + 2;
	}

	for(uint16_t i = 0 ; i < len ; i ++)
	{
		ptr += snprintf( app_datastrbuf + ptr , 200 - ptr , "%02X",app_databuf[i]);
	}
	
	//snprintf(app_datastrbuf, 200 , "%0.3f",g_SystemParam_Param.pdate);
	//memcpy(app_datastrbuf,(uint8_t * )&g_SystemParam_Param.pdate , 4);
	
	
	DEBUG("This Value will send:%s len:%d\r\n",app_datastrbuf,strlen((const char *)app_datastrbuf));
	
	//uint8_t test_buf[8] = {0x00 , 0x00, 0x34,0x12,0x00,0x00,0x38,0x00};
	
	BSP_LM78_StartSend((uint8_t *)app_datastrbuf, strlen((const char *)app_datastrbuf));
	
	APP_DataSend_BatteryReduce();
	
	return 0 ; 
}

void APP_DataSend_BatteryReduce(void)
{
	g_SystemParam_Config.battery=g_SystemParam_Config.battery - 0.02f;
	if(g_SystemParam_Config.battery <= 0 )
	{
		g_SystemParam_Config.battery = 0;
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

