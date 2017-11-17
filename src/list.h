#ifndef __LIST_H_
#define __LIST_H_
#include<stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>
#include <errno.h>
#include "types.h"

#define  true     1
#define  false    0

typedef struct node{
	int fd_data;
	unsigned char data_buf[updata_length];
	struct node* pNext;
}Node;

Node *head ;
extern bool createNodelist();
extern bool  addNode(Node * node);
extern bool deleteNode(int index);
extern bool updataNode(int index,unsigned char buf[]);
extern bool sendAllNode(int fd);
extern bool getdataNode(unsigned char buf[],unsigned char type);
int bytesToInt(unsigned char buf[], int offset);

#endif