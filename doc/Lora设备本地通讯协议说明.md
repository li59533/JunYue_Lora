# LN 压路机传感器通讯协议说明
## 1.采用协议
LN私有协议 + 上报私有协议 
###  1.1 协议格式
**LN协议格式**
```
// head len cmd tlv foot sum
typedef struct
{
    uint8_t head;
    uint16_t len;
    uint16_t inf
    uint8_t cmd;
    uint8_t * payload;
    uint8_t foot;
    uint8_t sum;
}LN_Protocol_t
```


### 1.2协议说明
​	**LN 协议**
* head ： 协议头部，为固定标识
* len :从head到sum的长度
* Inf:预留，用于兼容点对点、1对多、ACK等用途
* cmd：当前报文所属命令
* payload：当前cmd所包含的负载内容
* foot: 协议尾部，为固定标识
* sum:校验和，从head到foot

## 2.命令说明
### 2.1 支持命令
|序号|cmd|说明|名称|
|---|---|---|---|
|1|0x01|设置配置参数 请求|CMD_SetConf_Req|
|2|0x02|设置配置参数 应答|CMD_SetConf_Resp|
|3|0x03|获取配置参数 请求|CMD_GetConf_Req|
|4|0x04|获取配置参数 应答|CMD_GetConf_Resp|
|5|0x80|获取软件版本 请求|CMD_GetVersion_Req|
|6|0x81|获取软件版本 应答|CMD_GetVersion_Resp|
|7|0xc7|请求上报数据 请求|CMD_GetData_Req|
|8|0xc8|上报数据 应答|CMD_ReportData|


### 2.2 CMD说明

#### 2.2.1 设置配置参数
**请求**：CMD-> CMD_SetConf_Req (0x01)
**Payload **：TLV
协议如下：

|序号|Tag|Len|Value|说明|
|---|---|---|---|---|
|1|0x01|8|uint8_t [8]|SN码|
|2|0x02|4|float|X灵敏度|
|3|0x03|4|float|Y灵敏度|
|4|0x04|4|float|Z灵敏度|
|5|0x05|4|float|X ADC校准|
|6|0x06|4|float|Y ADC校准|
|7|0x07|4|float|Z ADC校准|
|8|0x08|1|uint8_t|电池当前电量|
|9|0x09|4|uint32_t|时间|
|10| 0x0a | 4    | uint32_t    | 休眠时间     |
| 11   |      |      |             |              |
||||||
||||||
||||||
**应答**
无

#### 2.2.2 获取配置参数

**请求**：CMD->CMD_GetConf_Req(0x03)
**Payload **：

无

**应答**：CMD->CMD_GetConf_Resp(0x04)
**Payload **：TLV
协议如下：

|序号|Tag|Len|Value|说明|
|---|---|---|---|---|
|1|1|8|uint8_t [8]|SN码|
|2|2|4|float|X灵敏度|
|3|3|4|float|Y灵敏度|
|4|4|4|float|Z灵敏度|
|5|5|4|float|X ADC校准|
|6|6|4|float|Y ADC校准|
|7|7|4|float|Z ADC校准|
|8|8|4|float|电池当前电量|
|9|9|4|uint32_t|时间|
|10| 10 | 4    | uint32_t    | 休眠时间     |
| 11   |      |      |             |              |
||||||
||||||
||||||
#### 2.2.3 获取软件版本
**请求**：CMD->CMD_GetVersion_Req(0x80)
**Payload **：无

无

**应答**
**Payload**:

```
typedef struct
{
    uint32_t version;
}Payload_t
```

uint32_t 为小端

0x00010203 为1.2.3版本

#### 2.2.4 请求数据
**请求**：CMD->CMD_GetData_Req(0xc7)
**Payload **：无

**应答**:CMD->CMD_ReportData(0xc8)

**Payload**:TLV
|序号|Tag|Len|Value|说明|
|---|---|---|---|---|
|1|1|4|float|X轴加速度|
|2|2|4|float|X轴速度|
|3|3|4|float|X轴位移|
|4|4|4|float|X轴峭度|
|5|5|4|float|X轴包络|
|6|6|4|float|Y轴加速度|
|7|7|4|float|Y轴速度|
|8|8|4|float|Y轴位移|
|9|9|4|float|Y轴峭度|
|10|10|4|float|Y轴包络|
|11|11|4|float|Z轴加速度|
|12|12|4|float|Z轴速度|
|13|13|4|float|Z轴位移|
|14|14|4|float|Z轴峭度|
|15|15|4|float|Z轴包络|
|16|16|4|float|温度|
|17|17|4|float|电量|








