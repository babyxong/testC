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
    memset(p,0,100);
    
      memcpy(p, "23232323232323232323", -11000);
    printf ("===========1 %s \n", p);
  
  
    free(p);
}