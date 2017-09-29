#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include "types.h"


Data_list_t datalist;
Data_up_t recvdata_list;
Http_cmd_list_t httpdata_list;

extern int Http_Socket_Fd;
//解析数据，将数据添加到对应的fd中
void Devdata_process(int fd,unsigned char buf[],int len){
	int data_len=len;
	unsigned char cmdbuf[3]={0x0E,0x00,0x00};
	//数据格式总长度25,封装后的数据是23,省去了校验位
	if(data_len==25)
		{
		memcpy(recvdata_list.data_buf,buf,data_len);
		memcpy(datalist.data_core.Head_byte,recvdata_list.data_core.Head_byte,2);
		memcpy(datalist.data_core.MAC_addr,recvdata_list.data_core.MAC_addr,4);
		memcpy(datalist.data_core.PM25,recvdata_list.data_core.PM25,3);
		memcpy(datalist.data_core.PM03,recvdata_list.data_core.PM03,3);
		memcpy(datalist.data_core.TEM,recvdata_list.data_core.TEM,3);
		memcpy(datalist.data_core.HUM,recvdata_list.data_core.HUM,3);
		memcpy(datalist.data_core.CMD,cmdbuf,3);
		memcpy(datalist.data_core.Tial,recvdata_list.data_core.Tial,2);
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
		switch(httpdata_list.data_core.cmd_type){
			case 0xAA:
				//拉取所有设备信息，发送所有节点信息给HTTP服务端
				sendAllNode(Http_Socket_Fd);
				break;
			case 0xAB:
				//控制设备信息
				break;
			default:
				break;
			}
		
		}
	else{
		}
}

