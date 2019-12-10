/**
 **************************************************************************************************
 * @file        app_conf.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_conf.h"
#include "stm32_bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "bsp_queue.h"
#include "lnprotocol.h"
#include "system_param.h"
#include "version.h"
/**
 * @addtogroup    app_conf_Modules 
 * @{  
 */

/**
 * @defgroup      app_conf_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Private_Variables 
 * @brief         
 * @{  
 */
static uint8_t  app_conf_dataspace[200] = { 0 };
/**
 * @}
 */
 
/**
 * @defgroup      app_conf_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_conf_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void app_conf_revprocess_ln(uint8_t * buf , uint16_t len);
static void app_lnswitch_cmd(uint8_t * buf,uint16_t len);
static void app_setconfreq_process(uint8_t *payload,uint16_t len);
static void app_getconfreq_process(uint8_t *payload,uint16_t len);
static void app_getversionreq_process(uint8_t *payload,uint16_t len);
/**
 * @}
 */

/**
 * @defgroup      app_conf_Functions 
 * @brief         
 * @{  
 */
 

void APP_Conf_TestUart(void)
{
	
}

void APP_Conf_SendBytes(uint8_t *buf , uint16_t len )
{
	BSP_Usart_WriteBytes_DMA(BSP_UART_2 , buf , len);
}

void APP_Conf_RevProcess(void)
{
	uint8_t * buf_ptr = 0;
	uint8_t len = 0;
	if(BSP_Queue_GetCount(BSP_QUEUE_UART2_REV) > 0)
	{
		buf_ptr = BSP_Queue_Dequeue(BSP_QUEUE_UART2_REV, &len);
		app_conf_revprocess_ln( buf_ptr , len);
		
	}
}


static void app_conf_revprocess_ln(uint8_t * buf , uint16_t len)
{
	ln_protocolintance_t *ln_protocolintance = (ln_protocolintance_t *)buf;
	if( ln_protocolintance->head == LNPROTOCOL_HEAD)
	{
		if(ln_protocolintance->len == len)
		{
			if(buf[len - 2] == LNPROTOCOL_FOOT)
			{
				if(LNprotocol_AddChecksum(buf,len - 1) == buf[len -1])
				{
					app_lnswitch_cmd(&ln_protocolintance->cmd,len - sizeof(ln_protocolintance) - 1);
				}
				else
				{
					DEBUG("APP_Rev Check sum is err");
				}
			}
			else
			{
				DEBUG("APP_Rev Foot is err\r\n");
			}
		}
		else
		{
			DEBUG("APP_Rev Len is err\r\n");
		}
	}
	else
	{
		DEBUG("APP_Rev Head is err\r\n");
	}	
}

static void app_lnswitch_cmd(uint8_t * buf,uint16_t len)
{
	uint8_t cmd = 0;
	cmd = buf[0];
	DEBUG("APP_REV CMD is %X\r\n",cmd);
	
	switch(cmd)
	{
		case CMD_SetConf_Req:app_setconfreq_process(buf + 1, len -1 );break;
		case CMD_GetConf_Req:app_getconfreq_process(buf + 1, len -1 ) ;break;
		case CMD_GetVersion_Req: app_getversionreq_process(buf + 1, len -1 );break;
		default:break;
	}
}

static void app_setconfreq_process(uint8_t *payload,uint16_t len)
{

	uint8_t * payload_ptr = 0;
	LN_Tlv_t * tlv_buf = 0;
	uint8_t result = CONF_SUCCESS;
	
	
	payload_ptr = payload;
	DEBUG("APP_Rev Payload LEN is %d\r\n",len);
	while(1)
	{
		tlv_buf = (LN_Tlv_t *) payload_ptr;
		DEBUG("APP_Rev Tag is %X\r\n",tlv_buf->Tag);
		switch(tlv_buf->Tag)
		{
			case TAG_SEND_INTERVAL:
			{
				if((tlv_buf->Value.BIT_32 <= 86400)&&(tlv_buf->Value.BIT_32 > 0))   // < 1 day (86400 s) and > 0 s
				{
					g_SystemParam_Config.sleep_time = tlv_buf->Value.BIT_32;
				}
				else
				{
					result = CONF_ERROR;
					DEBUG("TAG_SEND_INTERVAL is False\r\n");
				}
			}
			break;
			default:
			{
				result = CONF_ERROR;
				DEBUG("APP_Conf Tag is miss\r\n");
			}
			break;
		}
		
		payload_ptr = payload_ptr + tlv_buf->Len + 2 ;
		
		if((payload_ptr - payload)>= (len - 2))
		{
			break;
		}
	}

	if(result == CONF_ERROR)
	{
		DEBUG("APP_Conf is Err\r\n");
	}
	else
	{
		DEBUG("APP_Conf is SUCCESS then save\r\n");
		SystemParam_Save();
	}
	
}





// head len cmd tlv foot sum

static void app_getconfreq_process(uint8_t *payload,uint16_t len)
{
	ln_protocolintance_t *ln_protocolintance = (ln_protocolintance_t * )app_conf_dataspace;
	LN_Tlv_t tlv_value = { 0 };
	uint8_t  * payload_ptr = 0;
	float float_temp = 0.0;
	
	ln_protocolintance->head = LNPROTOCOL_HEAD;
	//ln_protocolintance->len = sizeof(ln_protocolintance_t);
	ln_protocolintance->inf = 0x00;
	ln_protocolintance->cmd = CMD_GetConf_Resp;
	
	payload_ptr = &ln_protocolintance->cmd + 1;
	
	// ------- mvToAcc_p---------------
	tlv_value.Tag = CMD_GetConf_Resp;
	tlv_value.Len = 4;
	tlv_value.Value.BIT_32 =  g_SystemParam_Config.sleep_time;

	payload_ptr += LN_AddTlv(payload_ptr, &tlv_value);
	// --------------------------------
	ln_protocolintance->len = (payload_ptr - &ln_protocolintance->head) + 1;
	*payload_ptr = LNPROTOCOL_FOOT;
	*(payload_ptr + 1) =  LNprotocol_AddChecksum((uint8_t * )&ln_protocolintance,ln_protocolintance->len - 1);
	
	APP_Conf_SendBytes(app_conf_dataspace,ln_protocolintance->len);
	
}

static void app_getversionreq_process(uint8_t *payload,uint16_t len)
{
	ln_protocolintance_t *ln_protocolintance = (ln_protocolintance_t * )app_conf_dataspace;
	uint8_t  * payload_ptr = 0;
	uint32_t version = 0 ;
	
	version = Version_Get_Bin();
	
	ln_protocolintance->head = LNPROTOCOL_HEAD;
	//ln_protocolintance->len = sizeof(ln_protocolintance_t);
	ln_protocolintance->inf = 0x00;
	ln_protocolintance->cmd = CMD_GetVersion_Resp;
	
	payload_ptr = &ln_protocolintance->cmd + 1;
	// -------version---------------
	memcpy(payload_ptr,&version,4);
	payload_ptr += 4;
	// --------------------------------
	ln_protocolintance->len = (payload_ptr - &ln_protocolintance->head) + 1;
	*payload_ptr = LNPROTOCOL_FOOT;
	*(payload_ptr + 1) =  LNprotocol_AddChecksum((uint8_t * )&ln_protocolintance,ln_protocolintance->len - 1);
	
	APP_Conf_SendBytes(app_conf_dataspace,ln_protocolintance->len);
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

