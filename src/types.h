#ifndef __TYPES_H__
#define __TYPES_H__

#define updata_length      	14  //updata to http data_length,and list save data_length
#define httpcmd_length     	11//
#define httpgetdata_length  	14//get data length

//node list,节点存储
typedef union Data_list
{
   unsigned char data_buf[updata_length];
   struct data_list_t
   {
       unsigned char MAC_addr[4];   //设备地址 
       unsigned char PM25[2];//第一个字节0x01,后两个是数据，数据为整数
       unsigned char TEM[2];//第一个字节0x03,后两个是数据,数据为1000+数据准换16
	unsigned char HUM[2];//第一个字节0x04,后两个是数据,数据为1000+数据准换16
	unsigned char CO2[2];
	unsigned char TVOC[2];
       //unsigned char CMD[2];//第一个字节是0x0E,后面是数据，控制设备状态
   }data_core;
}Data_list_t;

//检测类数据周期上报信息
typedef union Data_up
{
   unsigned char data_buf[23];
   struct data_up_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x17
       unsigned char Data_type; //数据的类型0x0C
       unsigned char MAC_addr[4];   //设备地址 
       unsigned char PM25[2];//第一个是0x08,后面是数据
       unsigned char TEM[2];//第一个字节0x06,后面是数据,温度通过加100，为了算零下温度
       unsigned char HUM[2];//第一个字节0x07,后面是数据
       unsigned char CO2[2];//0x09,
	unsigned char TVOC[2];//0x0A
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

//HTTP 获取单个设备信息
typedef union Http_getdata_list
{
   unsigned char data_buf[httpgetdata_length];
   struct http_getdata_list_t
   {
   	   unsigned char Head_byte[2];//0xEB 0x90
       unsigned char data_length[2];   //数据长度
       unsigned char cmd_type;//0x0A
	   unsigned char dev_data[4];
	   unsigned char data_type;//设备的类型:是二氧化碳，温度湿度，甲醛等等
       unsigned char Check_code[2];//校验码
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Http_getdata_list_t;

extern void Httpdata_process(unsigned char buf[],int len);
extern void Devdata_process(int fd,unsigned char buf[],int len);

extern void int_to_string (int n, char s[]);
extern int bytesToInt(unsigned char buf[], int offset);

#endif
