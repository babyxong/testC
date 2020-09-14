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
        
    int *p;
    
    
    
    p = malloc(100);
    
    printf ("===========1 %p \n", p);
  
    free(p);
}