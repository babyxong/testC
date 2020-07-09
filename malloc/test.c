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
 
int main()
{
    char * pchar;
    
    
    int *p;
    
    p = malloc (0);
    
    printf("malloc ===  %p   \n", p);
    
    *p =1;
    printf("free ===  %d  \n",  *p);
    
    printf("free ==1= \n");
    free(p);
    printf("free ==2=  %p   \n", p);
   
}