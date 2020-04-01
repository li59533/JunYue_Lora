/**
 **************************************************************************************************
 * @file        net_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "osal.h"
#include "clog.h"
#include "net_task.h"


/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_led.h"
#include "bsp_e32.h"
#include "bsp_ad7682.h"
#include "bsp_lm78.h"
/**
 * @addtogroup    net_task_Modules 
 * @{  
 */

/**
 * @defgroup      net_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      net_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      net_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      net_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      net_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      net_task_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t g_NetTask_Id = 0;
/**
 * @}
 */

/**
 * @defgroup      net_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      net_task_Functions 
 * @brief         
 * @{  
 */
void NetTask_Init(uint8_t taskId)
{
    g_NetTask_Id = taskId;
	NetTask_Send_Event(NET_TASK_MODULE_INIT_EVENT);
	
	BSP_LM78_Init();
	BSP_LED_Blink(BSP_LED_TEST, 3, 50, 1000);
	NetTask_Timer_Start_Event(NET_TASK_LOOP_EVENT,5000);
	//NetTask_Send_Event(NET_TASK_AT_PROCESS_EVENT);
	//NetTask_Send_Event(NET_TASK_SEND_AT_EVENT);
}

osal_event_t NetTask_Process(uint8_t taskid,osal_event_t events)
{
    if (events & NET_TASK_LOOP_EVENT)
    {
		DEBUG("NET_TASK_LOOP_EVENT\r\n");
		
		char buf[30];
		sprintf( buf ,"%f", BSP_AD7682_GetAvalue());
		DEBUG("BSP_AD7682_GetAvalue:%s\r\n" ,buf );
		char temp_test[] = "123456";
		BSP_LM78_StartSend((uint8_t *)buf, strlen(buf));
		
		BSP_LED_Blink(BSP_LED_TEST, 3, 20, 100);
		NetTask_Timer_Start_Event(NET_TASK_LOOP_EVENT,10000);
		NetTask_Timer_Start_Event(NET_TASK_TESTLED_EVENT,1000);
        return events ^ NET_TASK_LOOP_EVENT;
    }

	
    if (events & NET_TASK_TESTLED_EVENT)
    {
		BSP_LED_Blink(BSP_LED_TEST, 0, 50, 500);
        return events ^ NET_TASK_TESTLED_EVENT;
    }		
	

    if (events & NET_TASK_AT_PROCESS_EVENT)
    {
		
		BSP_LM78_RespProcess();
		DEBUG("NET_TASK_AT_PROCESS_EVENT\r\n");
	
        return events ^ NET_TASK_AT_PROCESS_EVENT;
    }	

    if (events & NET_TASK_SEND_AT_EVENT)
    {
		
		BSP_LM78_ReqProcess();
		DEBUG("NET_TASK_SEND_AT_EVENT\r\n");
	
        return events ^ NET_TASK_SEND_AT_EVENT;
    }		
	
	
    return 0;
}

void NetTask_Send_Event(osal_event_t events)
{
    OS_Events_Set(g_NetTask_Id,events);
}

void NetTask_Timer_Start_Event(osal_event_t event_flag,uint32_t timeout)
{
	OS_Timer_Start(g_NetTask_Id, event_flag,timeout);	
}

void NetTask_Timer_Stop_Event(osal_event_t event_flag)
{
	OS_Timer_Stop(g_NetTask_Id,event_flag);
}

void NetTask_Clear_Event(osal_event_t events)
{
	OS_Events_Clear(g_NetTask_Id,events);
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

