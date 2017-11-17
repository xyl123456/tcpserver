#include "list.h"
#include "cJSON.h"
extern Http_Socket_Fd;


extern Data_list_t datalist;//节点存储的数据格式
extern Data_up_t recvdata_list;
extern Http_cmd_list_t httpdata_list;
extern Http_getdata_list_t  httpgetdata_list;


//创建链表，头结点data=0;pNext=null

bool createNodelist()
{
	head = (Node*)malloc(sizeof(Node));
	if(NULL == head){
		return false;
		}
	else {
		head->fd_data =0;
		memset(head->data_buf,0,19);
		head->pNext = NULL;
		return true;
		}
}

//增加节点尾部添加
bool  addNode(Node * node)
{
	if(NULL == head){
		return false;
		}
	Node* p = head ->pNext;
	Node* q = head;
	while(NULL !=p){
		q = p;
		p = p->pNext;
		}
	q->pNext = node;
	node ->pNext = NULL;
	return true;
}

//删除节点
bool deleteNode(int index)
{
	if(NULL == head){
		return false;
		}
	
	Node* perior = head;
	Node* q = head->pNext;
	while((q!=NULL)&&(q->fd_data != index))
		{
		perior = q;
		q = q->pNext;
		}
	if(q->fd_data == index)
		{
		memset(q->data_buf,0,updata_length);
		if(q->pNext == NULL)
			{
			perior->pNext = NULL;
		        free(q);
			return true;
			}
		else
			{
			perior->pNext = q->pNext;
    			free(q);
			return true;
			}
		}
}

//逆序
void reverseNodeList()
{
	if(NULL == head){
		return ;
		}
	if(head->pNext == NULL){
		return;
		}
	Node* p = head->pNext;
	Node* q = p->pNext;
	Node*  t = NULL;
	while(NULL != q){
		t = q->pNext;
		q->pNext = p;
		p = q;
		q = t;
		}
	head->pNext->pNext = NULL;
	head->pNext =p;
}
//降序
void sort()
{
	Node* pHead = head;
	if(head == NULL){
		return;
		}
	if(pHead->pNext == NULL){
		return;
		}
	Node* pi = pHead->pNext;
	Node* pj = pi->pNext;
	for(;pi != NULL;pi= pi->pNext){
		for(pj = pi->pNext;pj != NULL;pj=pj->pNext){
			if(pj->fd_data>pi->fd_data){
				int tmp = pj->fd_data;
				pj->fd_data = pi->fd_data;
				pi->fd_data = tmp;
				}
			}
		}
}
//销毁
void destroyNodeList()
{
	if(NULL == head){
		return;
		}
	if(NULL == head->pNext){
		free(head);
		head =NULL;
		return;
		}
	Node* p = head->pNext;
	while(NULL != p){
		Node* tmp =p;
		p = p->pNext;
		free(tmp);
		}
	free(head);
	head = NULL;
}

//更新节点数据
bool updataNode(int index,unsigned char buf[])
{
	if(NULL == head){
		return false;
		}
	Node* perior = head;
	Node* q = head->pNext;
	while((q!=NULL)&&(q->fd_data != index))
		{
		perior = q;
		q = q->pNext;
		}
	if(q->fd_data == index)
		{
		memcpy(q->data_buf,buf,updata_length);
		//write(Http_Socket_Fd,q->data_buf,updata_length);
		return true;
		}
}

bool sendAllNode(int fd)
{
	if(NULL == head){
		return false;
		}
	Node* q = head->pNext;
	Data_list_t nod_datalist;
	
	//创建一个空白的JSON对象
	cJSON *json = cJSON_CreateObject();
	//创建一个数组到JSON对象中
	cJSON *array = NULL;
	cJSON_AddItemToObject(json,"dev_ids",array=cJSON_CreateArray());
	while(q!=NULL)
		{
		memcpy(nod_datalist.data_buf,q->data_buf,updata_length);
		int devid=bytesToInt(nod_datalist.data_core.MAC_addr,4);
		
		//printf("the mac is:%d\n",devid);
		char devidstring[5];
		int_to_string(devid,devidstring);
		//printf("the string is:%s\n",devidstring);
		cJSON_AddItemToArray(array,cJSON_CreateString(devidstring));
		q = q->pNext;
		}
	char *sendbuf = cJSON_Print(json);
	write(fd,sendbuf,strlen(sendbuf));
	
	cJSON_Delete(json);
	return true;
}

//find by device_mac
bool getdataNode(unsigned char buf[],unsigned char type)
{
	if(NULL == head){
		return false;
		}
	Node* perior = head;
	Node* q = head->pNext;
	Data_list_t nod_datalist;

	while(q!=NULL)
		{
		memcpy(nod_datalist.data_buf,q->data_buf,updata_length);
		if(memcmp(nod_datalist.data_core.MAC_addr,buf,4)==0){

		//创建一个空白的JSON对象
		cJSON *json = cJSON_CreateObject();
			
			//返回设备状态信息
			int devid=bytesToInt(nod_datalist.data_core.MAC_addr,4);
			char devidstring[5];
			int_to_string(devid,devidstring);
			
			cJSON_AddItemToObject(json,"dev_id",cJSON_CreateString(devidstring));

			//创建一个数组到JSON对象中
			cJSON *array = NULL;
			cJSON_AddItemToObject(json,"datas",array=cJSON_CreateArray());
			//数组上添加对象
			cJSON *obj = NULL;
			cJSON_AddItemToArray(array,obj=cJSON_CreateObject());

			switch(type){
				case 0xAA:
						{
						int pm25=bytesToInt(nod_datalist.data_core.PM25, 3);
						int tem=bytesToInt(nod_datalist.data_core.TEM, 3);
						int hum=bytesToInt(nod_datalist.data_core.HUM, 3);
						int co2=bytesToInt(nod_datalist.data_core.CO2, 3);
						int tvoc=bytesToInt(nod_datalist.data_core.TVOC,3);
						int cmd=bytesToInt(nod_datalist.data_core.CMD,3);
						char pm25string[5];
						char temstring[5];
						char humstring[5];
						char co2string[5];
						char tvocstring[5];
						char cmdstring[5];
						int_to_string(pm25,pm25string); 
						int_to_string(tem,temstring);
						int_to_string(hum,humstring);
						int_to_string(co2,co2string);
						int_to_string(tvoc,tvocstring);
						int_to_string(cmd,cmdstring);
						cJSON_AddItemToObject(obj,"PM25",cJSON_CreateString(pm25string));
						cJSON_AddItemToObject(obj,"TEM",cJSON_CreateString(temstring));
						cJSON_AddItemToObject(obj,"HUM",cJSON_CreateString(humstring));
						cJSON_AddItemToObject(obj,"CO2",cJSON_CreateString(co2string));
						cJSON_AddItemToObject(obj,"TVOC",cJSON_CreateString(tvocstring));
						cJSON_AddItemToObject(obj,"CMD",cJSON_CreateString(cmdstring));	
						//所有信息都要上传显示
					}
					break;
				case 0x21:
					{
						int tem=bytesToInt(nod_datalist.data_core.TEM, 3);
						int hum=bytesToInt(nod_datalist.data_core.HUM, 3);
						char temstring[5];
						char humstring[5];
						int_to_string(tem,temstring);
						int_to_string(hum,humstring);
						cJSON_AddItemToObject(obj,"TEM",cJSON_CreateString(temstring));
						cJSON_AddItemToObject(obj,"HUM",cJSON_CreateString(humstring));
						//温度、湿度信息
					}
					break;
				case 0x22:
						{
						int pm25=bytesToInt(nod_datalist.data_core.PM25, 3);
						char pm25string[5];
						int_to_string(pm25,pm25string);
						cJSON_AddItemToObject(obj,"PM25",cJSON_CreateString(pm25string));	
					}
					break;
				case 0x23:
						{
					    int co2=bytesToInt(nod_datalist.data_core.PM25, 3);
						char co2string[5];
						int_to_string(co2,co2string);
						cJSON_AddItemToObject(obj,"CO2",cJSON_CreateString(co2string));
					}
					break;
				case 0x24:
						{
						int tvoc=bytesToInt(nod_datalist.data_core.TVOC,3);
						char tvocstring[5];
						int_to_string(tvoc,tvocstring);
						cJSON_AddItemToObject(obj,"TVOC",cJSON_CreateString(tvocstring));
					}
					break;
				case 0x25:
						{
						int cmd=bytesToInt(nod_datalist.data_core.CMD,3);
						char cmdstring[5];
						int_to_string(cmd,cmdstring);
						cJSON_AddItemToObject(obj,"CMD",cJSON_CreateString(cmdstring));	
					}
					break;
				default :
					break;
				}
			char *sendbuf = cJSON_Print(json);
			write(Http_Socket_Fd,sendbuf,strlen(sendbuf));
			cJSON_Delete(json);
			break;
			}
		else{
		perior = q;
		q = q->pNext;
			}
		}
}
