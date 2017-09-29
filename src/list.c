#include "list.h"
extern Http_Socket_Fd;
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
	while(q!=NULL)
		{
		write(fd,q->data_buf,updata_length);
		q = q->pNext;
		}
		
	return true;
}
