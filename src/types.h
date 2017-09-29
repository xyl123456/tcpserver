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
       unsigned char MAC_addr[4];   //�豸��ַ 
       unsigned char PM25[3];//��һ���ֽ�0x01,�����������ݣ�����Ϊ����
       unsigned char PM03[3];//��һ���ֽ�0x0E,�����������ݣ�����Ϊ����
       unsigned char TEM[3];//��һ���ֽ�0x03,������������,����Ϊ1000+����׼��16
       unsigned char HUM[3];//��һ���ֽ�0x04,������������,����Ϊ1000+����׼��16
       unsigned char CMD[3];//��һ���ֽ���0x0E,���������ݣ������豸״̬
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
       unsigned char Data_type; //���ݵ�����0x04
       unsigned char MAC_addr[4];   //�豸��ַ 
       unsigned char PM25[3];//��һ���ֽ�0x01,�����������ݣ�����Ϊ����
       unsigned char PM03[3];//��һ���ֽ�0x0E,�����������ݣ�����Ϊ����
       unsigned char TEM[3];//��һ���ֽ�0x03,������������,����Ϊ1000+����׼��16
       unsigned char HUM[3];//��һ���ֽ�0x04,������������,����Ϊ1000+����׼��16
       unsigned char Check_code[2];//У���룬��ȥ��ͷ�Ͱ�β�����ֽڵ��ۼӺ�
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Data_up_t;

//http cmd ������������ȡ�����豸��Ϣ�����Ƶ����豸����
typedef union Http_cmd_list
{
   unsigned char data_buf[httpcmd_length];
   struct http_cmd_list_t
   {
   	   unsigned char Head_byte[2];//0xEB 0x90
       unsigned char data_length[2];   //���ݳ���
       unsigned char cmd_type;
	   unsigned char cmd_data[2];
       unsigned char Check_code[2];//У����
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Http_cmd_list_t;

extern void Httpdata_process(unsigned char buf[],int len);
extern void Devdata_process(int fd,unsigned char buf[],int len);

#endif
