/**
 **************************************************************************************************
 * @file        lnprotocol.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _LNPROTOCOL_H_
#define _LNPROTOCOL_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    lnprotocol_Modules 
 * @{  
 */

/**
 * @defgroup      lnprotocol_Exported_Macros 
 * @{  
 */
#define LNPROTOCOL_HEAD			0X7E

#define LNPROTOCOL_FOOT			0X7E


/**
 * @}
 */

/**
 * @defgroup      lnprotocol_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      lnprotocol_Exported_Types 
 * @{  
 */
typedef enum 
{
	TAG_SEND_INTERVAL = 0x01 , // sending interval	
	
	
	
}LN_Protocol_Tag_e;

typedef enum
{
	CONF_SUCCESS = 1,
	CONF_ERROR	 = 2,
}LN_Conf_Status_e;


typedef enum
{
	CMD_SetConf_Req = 0x01,
	CMD_SetConf_Resp = 0x02,
	CMD_GetConf_Req = 0x03,
	CMD_GetConf_Resp = 0x04,
	
	CMD_GetVersion_Req = 0x80,
	CMD_GetVersion_Resp = 0x81,
}LN_Protocol_Cmd_e;



#pragma pack(1)
typedef struct
{
	uint8_t Tag;
	uint8_t Len;
	union 
	{
		uint8_t BIT_8;
		uint16_t BIT_16;
		uint32_t BIT_32;
		uint8_t Array[20];
	}Value;
}LN_Tlv_t;


typedef struct
{
	uint8_t head;
	uint16_t len;
	uint16_t inf;
	uint8_t cmd;
	uint8_t *payload;
	uint8_t foot;
	uint8_t sum;
}ln_protocolintance_t;


#pragma pack()

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_Exported_Functions 
 * @{  
 */
uint8_t * LNprotocol_AddHead(uint8_t * targetspace_ptr); // return the value ptr

uint8_t * LNprotocol_AddValue(uint8_t * targetspace_ptr , uint8_t *buf,uint8_t len);

uint8_t * LNprotocol_AddFoot(uint8_t * targetspace_ptr);

void LNprotocol_Addlen(uint8_t *buf, uint16_t len);

uint8_t LNprotocol_AddChecksum(uint8_t * buf,uint16_t len);

uint8_t LN_AddTlv(uint8_t * disaddr,LN_Tlv_t * tlv_value);

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
