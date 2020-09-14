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
 
  /*
  
    
  相当于  int *p = 调用的部分的值
  */
 void Fun(int *p)
 {
    printf ("FUN ***********0 %p\n", p);
    printf ("FUN ***********0& %p\n", &p);
    free (p);
    p = NULL;
 }
 
int main()
{    
        
    int *p;
    
    printf ("===========0 %p \n", p);
    
    p = malloc(100);
    
    
    printf ("===========1 %p \n", p);
    printf ("===========1& %p \n", &p);
    
    Fun(p);
    
    printf ("===========2 %p \n", p);
    
    *(p+10) = 1000;
    
    printf ("===========3 %p \n", p);
    
    free (p);
    
    
    
    printf ("===========2 %p \n" , p);
    
}