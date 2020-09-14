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

typedef struct stFunIN1{
     int AAA;
     void *pA;	
	 int  (*funP)(struct stFunIN1 * pA);
 }stAAA;
 


 int Func(stAAA *p)
 {
	 printf ("free ==== start \n");
	 printf ("free :%p \n", p);
	 free(p);
	 //*p = NULL;
	 printf ("free ====ok \n");	 
	 
	 
	 return 10000;
 }
 
int main()
{    
	int num = 0;
    
    stAAA *Ptest ; 
	stAAA *Ptest1;
	Ptest = malloc(sizeof(stAAA));
	
	printf ("malll :%p \n", Ptest);
    
	
   	
	printf ("will core ==== %p \n", Ptest);
	Ptest->funP = Func;
	
	printf ("fun test 1 core ==== %p \n", Ptest);
	num = Ptest->funP(Ptest);
	
	Ptest1 = malloc(sizeof(stAAA));
	
	printf ("fun test 2 core ==== %p \n", Ptest);
	num = Ptest->funP(Ptest);
	printf ("fun test end ==== %p \n", Ptest);
	Ptest->AAA = 10;
	
	
    printf ("mail ==== over num:%d \n", num);
}


