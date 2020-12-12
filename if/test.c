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

void fun(void)
{
    
}

int main()
{
    char * pchar;
    
    {
        int n = 123;
        printf(" ==0= n:%d np:%p   \n", n, &n);
        
    }
    {
         int n;
         printf(" ==1= n:%d  np:%p   \n",n, &n);
    }
    
    
    int *p;
    
    p = malloc (100);
    
    printf("malloc ===  %p   \n", p);
    free(p);
    
    printf("free ===  %p   \n", p);
    
    printf("free ==1= \n");
    free(p);
    printf("free ==2=  %p   \n", p);

    
}