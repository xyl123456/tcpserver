#ifndef __TYPES_H__
#define __TYPES_H__

#define updata_length      	14  //updata to http data_length,and list save data_length
#define httpcmd_length     	11//
#define httpgetdata_length  	14//get data length

//node list,�ڵ�洢
typedef union Data_list
{
   unsigned char data_buf[updata_length];
   struct data_list_t
   {
       unsigned char MAC_addr[4];   //�豸��ַ 
       unsigned char PM25[2];//��һ���ֽ�0x01,�����������ݣ�����Ϊ����
       unsigned char TEM[2];//��һ���ֽ�0x03,������������,����Ϊ1000+����׼��16
	unsigned char HUM[2];//��һ���ֽ�0x04,������������,����Ϊ1000+����׼��16
	unsigned char CO2[2];
	unsigned char TVOC[2];
       //unsigned char CMD[2];//��һ���ֽ���0x0E,���������ݣ������豸״̬
   }data_core;
}Data_list_t;

//��������������ϱ���Ϣ
typedef union Data_up
{
   unsigned char data_buf[23];
   struct data_up_t
   {
       unsigned char Head_byte[2];//0xEB 0x90
       unsigned char Data_length[2];//0x00 0x17
       unsigned char Data_type; //���ݵ�����0x0C
       unsigned char MAC_addr[4];   //�豸��ַ 
       unsigned char PM25[2];//��һ����0x08,����������
       unsigned char TEM[2];//��һ���ֽ�0x06,����������,�¶�ͨ����100��Ϊ���������¶�
       unsigned char HUM[2];//��һ���ֽ�0x07,����������
       unsigned char CO2[2];//0x09,
	unsigned char TVOC[2];//0x0A
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

//HTTP ��ȡ�����豸��Ϣ
typedef union Http_getdata_list
{
   unsigned char data_buf[httpgetdata_length];
   struct http_getdata_list_t
   {
   	   unsigned char Head_byte[2];//0xEB 0x90
       unsigned char data_length[2];   //���ݳ���
       unsigned char cmd_type;//0x0A
	   unsigned char dev_data[4];
	   unsigned char data_type;//�豸������:�Ƕ�����̼���¶�ʪ�ȣ���ȩ�ȵ�
       unsigned char Check_code[2];//У����
       unsigned char Tial[2];//0x0D 0x0A
   }data_core;
}Http_getdata_list_t;

extern void Httpdata_process(unsigned char buf[],int len);
extern void Devdata_process(int fd,unsigned char buf[],int len);

extern void int_to_string (int n, char s[]);
extern int bytesToInt(unsigned char buf[], int offset);

#endif
