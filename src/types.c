#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include "types.h"


Data_list_t datalist;//�ڵ�洢����
Data_up_t recvdata_list;//�����ϱ���ʽ
Http_cmd_list_t httpdata_list;
Http_getdata_list_t  httpgetdata_list;
	
extern int Http_Socket_Fd;
//�������ݣ���������ӵ���Ӧ��fd��
void Devdata_process(int fd,unsigned char buf[],int len){
	int data_len=len;
	//
	if((data_len==31)&&(buf[4]==0x0C))
		{
		memcpy(recvdata_list.data_buf,buf,data_len);
		memcpy(datalist.data_core.MAC_addr,recvdata_list.data_core.MAC_addr,4);
		memcpy(datalist.data_core.PM25,recvdata_list.data_core.PM25,3);
		memcpy(datalist.data_core.TEM,recvdata_list.data_core.TEM,3);
		memcpy(datalist.data_core.HUM,recvdata_list.data_core.HUM,3);
		memcpy(datalist.data_core.CO2,recvdata_list.data_core.CO2,3);
		memcpy(datalist.data_core.TVOC,recvdata_list.data_core.TVOC,3);
		memcpy(datalist.data_core.CMD,recvdata_list.data_core.CMD,3);

		updataNode(fd, datalist.data_buf);
		}
	else{
		printf("the data length is error!\n");
		}
	//write(Http_Socket_Fd,datalist.data_buf,updata_length);
}

void Httpdata_process(unsigned char buf[],int len)
{
	int data_len=len;
	if(data_len==httpcmd_length)
		{
		memcpy(httpdata_list.data_buf,buf,data_len);
		if(httpdata_list.data_core.cmd_type==0xAA){
			sendAllNode(Http_Socket_Fd);
			}
		}
	else{
		if(data_len=httpgetdata_length)
			{
			//get data ��ȡ�����豸��Ϣ
			memcpy(httpgetdata_list.data_buf,buf,data_len);	
			unsigned char data_type=httpgetdata_list.data_core.data_type;
			getdataNode(httpgetdata_list.data_core.dev_data,data_type);
			}
		}
}

void int_to_string (int n,char s[])
{

		if(n/1000!=0){
			s[0]=n/1000+'0';
			s[1]=n%1000/100+'0';
			s[2]=n%100/10+'0';
			s[3]=n%10+'0';
			s[4]='\0';
			}
		else{
		if(n/100!=0){
			s[0]=n/100+'0';
			s[1]=n%100/10+'0';
			s[2]=n%10+'0';
			s[3]='\0';
			}else{
			if(n/10!=0)
				{
				s[0]=n/10+'0';
				s[1]=n%10+'0';
				s[2]='\0';
				}
			else
				{
				s[0]=n%10+'0';
				s[1]='\0';
				}
			 }
			}	
		
}

int bytesToInt(unsigned char buf[], int offset)
{ 
	int value;    
	if(offset==4)
		{
  	value = (int) ((buf[offset-1] & 0xFF)   
         | ((buf[offset-2] & 0xFF)<<8) 
         |((buf[offset-3] & 0xFF)<<16)
         |((buf[offset-4] & 0xFF)<<24));  
    return value; 
		}
	if(offset==3)
		{
		value = (int) ((buf[offset-1] & 0xFF)   
         | ((buf[offset-2] & 0xFF)<<8));
    return value; 
		}
	if(offset==2)
		{
		value = (int) (buf[offset-1] & 0xFF);
		return value;
		}

}

