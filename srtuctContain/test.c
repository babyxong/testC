/*******************************
client.c
********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8888
 
 #define STRING  "Hello World!!!!  mem ok"

 typedef struct SimSCSIReqOps SimSCSIReqOps_t;

 typedef struct SimSCSIRequest{	
	int a;
	int b;
	SimSCSIReqOps_t *ops;	
}SimSCSIRequest_t;


struct SimSCSIReqOps {	
	void (*freeReq)(SimSCSIRequest_t *req);			  ///< 释放命令发送时申请的ioBase空间
    int (*sendCommand)(SimSCSIRequest_t *req, char *buf); 
    void (*readData)(SimSCSIRequest_t *req);
    void (*writeData)(SimSCSIRequest_t *req);
    char *(*getBuf)(SimSCSIRequest_t *req);
};


 
int func(SimSCSIRequest_t *req, char *buf)
{

	printf ("fun test 1 core ==== %s \n",buf);
	
}

SimSCSIReqOps_t funtable ={
	
	.sendCommand = func,
};



int main()
{    
	SimSCSIRequest_t stSimReq;
	char cbuf[] ="fk you !\n";
	
	
	printf ("stSimReq.ops : %p \n"  , stSimReq.ops);
	stSimReq.ops = &funtable;
	
	
	stSimReq.ops->sendCommand(&stSimReq,  cbuf);
	
}


