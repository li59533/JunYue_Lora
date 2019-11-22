/**
 **************************************************************************************************
 * @file        system_param.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _SYSTEM_PARAM_H_
#define _SYSTEM_PARAM_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_Exported_Macros 
 * @{  
 */
#define SYSTEMPARAM_CONFIG     0

#define SYSTEMPARAM_SAVE_SPACE_LEN   0x1000
#define SYSTEMPARAM_SAVE_FIRST_ADDR   0x081FE000
#define SYSTEMPARAM_SAVE_SECOND_ADDR  0x081FF000

/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Types 
 * @{  
 */
#pragma pack(1)
typedef enum 
{
	PARAMETERMODE = 1,
	WAVEMODE = 2,
	FFTWAVEMODE = 3,
	FFTPARAMETERMODE = 4,
	IDLEMODE = 5,
	LITEWAVEMODE = 6
}DataToBoard_TYPE;


typedef enum 
{
	TYPE_NONE = 0,
	TYPE_MA = 1,
	TYPE_V = 2, 
	TYPE_IEPE = 3,
	TYPE_PT = 4,
	TYPE_HBR = 5,
	TYPE_AC_V = 6,
}INTERFACE_TYPE;
typedef enum 
{
	UNIT_NONE = 0,
	UNIT_V = 1,
	UNIT_A = 2,
	UNIT_KV = 3,
	UNIT_TEMP = 4,
	UNIT_M = 5,
	UNIT_M_S = 6,
	UNIT_M_S2 = 7,
	UNIT_G = 8,
	UNIT_MA = 9,
	UNIT_DB = 10,
	UNIT_MM_S = 11,
}INTERFACE_UNIT;

typedef enum 
{
	Greater=0,
	Equal=1,
	Less=2
}Equality_relation;

typedef enum 
{
	AND=0,
	OR
}Logical_relation;

typedef enum 
{
	daois=0,
	sdaOR
}Parameter_name;

typedef struct
{
	bool 	End_statue;  //是否为该通道的最后一条报警源
	uint8_t channel_number;
	Parameter_name parameter_NAME;
 	Logical_relation logical; //报警源逻辑关系
	Equality_relation relationship; //报警源与阈值等式关系
	float gatedata;
}RULE;

typedef struct
{
	uint16_t vaildsign;
	uint8_t baundrate;    /* =0:600    =1:1200 		=2:2400 		=3:4800 		=4:9600 */
	uint8_t addr; 
	uint8_t SNnumber[8]; 
	uint8_t parity;		// =0 : n,8,1   =1: o,8,1  =2: e,8,1	 数据格式
	float floatscale[12];
	//float floatrange[12];
	uint8_t DisplayMode;  // 显示模式　=0　固定　=1 循环
	uint8_t interface_type[12]; // 输入类型
	uint8_t unit[12];  // 单位
	float floatrange[12]; // 转换系数
	float floatadjust[12]; // 修正值
	//uint16_t interface_addr[12]; // modbus 地址 上传
	float alarmgate[6]; // 绝对值
	float floatadc[6]; // 绝对值
	uint8_t means	;// 均值类型
	uint16_t means_times; // 均值积算周期
	uint16_t freq;  // 采样频率 Hz
	uint16_t avr_count;
	uint8_t reflash; // 刷新时间 
	uint16_t din_addr;  //  开关量输入寄存器地址
	uint16_t dout_addr; //  开关量输出寄存器地址
	uint32_t force_gate,force_backlash;  // 应变启动阈值， 回差。
	uint16_t max_addr0,max_addr1;        //
	uint16_t vlpsseconds;            //  
	uint16_t vlprseconds;           //
	uint16_t runseconds;           //
	uint16_t pga;                 //
	uint16_t workcycleseconds;   //  工作周期
	uint16_t fangda;            //  放大倍数
	uint16_t boardset;         // 发射功率设置
	uint16_t ADtime;          //AD单次采样时间
	uint16_t ADfrequence;    //AD采样频率
	  
	uint64_t alarmminutetime;  //开始报警时间
	uint32_t FLASH_WRADDR;    //flash起始地址
	uint8_t  DataToBoardMode; 
	uint16_t  DataToSendChannel;
	uint8_t  DHCP;
	char APssid[20];
	char APpassword[20];
	char TcpServer_IP[20];
	char TcpServer_Port[10];
	char LocalIP[20];
	char LocalGATEWAY[20];
	char LocalMASK[20];
	uint32_t PeriodTransimissonCounter;
	uint8_t PeriodTransimissonStatus;
	uint8_t ParameterTransimissonStatus;
	uint8_t RequirePeriodChannel; //请求哪些单次波形的通道
	uint8_t RESETTIME;
	uint8_t Enable_active_beacon;
	uint8_t Iap_flag;
	uint32_t Iap_datalength;
	uint32_t channel_freq[12];
	uint32_t BeaconInterval;
	char server_address[20];
	char DNS_SERVERIP[20];
	uint8_t Lowpower_Mode;
	uint8_t scan_channel;
	uint8_t Waitforsleeptime;
	uint8_t WaitforIEPEtime;
	float  filterMean[6];
	uint32_t WaitToPeriodTransmissonCounter;
	float Alarm_value_junyue[20];//给君悦的20个报警值
	float battery;//给君悦的20个报警值
	uint16_t workcycleseconds_inAlarmStatue;
	int16_t tempCompensation; 
	uint8_t Alarm_source_number[10];//10个规则，每个规则的报警源数目，为0则不报警。
	RULE Alarm_source[10][20]; //二维数组，最多10个规则，每个规则最多20个报警源
	
    uint16_t crc;           /*!< 所有的参数结构体必须按字节对其。且最后一个必须包
                                 含一个uint16_t类型的数据，该数据用于内部存储时的
                                 crc校验和存储，用户在保存参数时不用关心该值数值。*/
}SystemParam_Config_t;
#pragma pack()
/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Variables 
 * @{  
 */
extern SystemParam_Config_t g_SystemParam_Config;
/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Functions 
 * @{  
 */
void SystemParam_Init(void);
int16_t SystemParam_Read(void);
void SystemParam_Save(void);
void SystemParam_Reset(void);
void SystemParam_Apply(void);
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
