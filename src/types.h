#ifndef __TYPES_H__
#define __TYPES_H__
#define updata_length      23  //updata to http data_length,and list save data_length
#define httpcmd_length     11//
typedef union Data_list
{
   unsigned char data_buf[updata_length];
   struct data_list_t
   {
   	   unsigned char Head_byte[2];//0xEB 0x90
       unsigned char MAC_addr[4];   //设备地址 
       unsigned char PM25[3];//第一个字节0x01,后两个是数据，数据为整数
       unsigned char PM03[3];//第一个字节0x0E,后两个是数据，数据为整数
       unsigned char TEM[3];//第一个字节0x03,后两个是数据,数据为1000+数据准换16
       unsigned char HUM[3];//第一个字节0x04,后两个是数据,数据为1000+数据准换16
       unsigned char CMD[3];//第一个字节是0x0E,后面是数据，控制设备状态
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Data_list_t;

typedef union Data_up
{
   unsigned char data_buf[25];
   struct data_up_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x17
       unsigned char Data_type; //数据的类型0x04
       unsigned char MAC_addr[4];   //设备地址 
       unsigned char PM25[3];//第一个字节0x01,后两个是数据，数据为整数
       unsigned char PM03[3];//第一个字节0x0E,后两个是数据，数据为整数
       unsigned char TEM[3];//第一个字节0x03,后两个是数据,数据为1000+数据准换16
       unsigned char HUM[3];//第一个字节0x04,后两个是数据,数据为1000+数据准换16
       unsigned char Check_code[2];//校验码，除去包头和包尾所有字节的累加和
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Data_up_t;

//http cmd 解析，包含获取整个设备信息，控制单个设备命令
typedef union Http_cmd_list
{
   unsigned char data_buf[httpcmd_length];
   struct http_cmd_list_t
   {
   	   unsigned char Head_byte[2];//0xEB 0x90
       unsigned char data_length[2];   //数据长度
       unsigned char cmd_type;
	   unsigned char cmd_data[2];
       unsigned char Check_code[2];//校验码
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Http_cmd_list_t;

extern void Httpdata_process(unsigned char buf[],int len);
extern void Devdata_process(int fd,unsigned char buf[],int len);

#endif
