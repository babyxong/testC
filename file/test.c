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
 
#define ROUND_UP_INI(x , a)  (((x) % (a)) ? ((x) / (a) +1):((x)/(a)))
#define ROUND_UP(x , a)  ( ((x)+(a-1)) & ~(a -1))
 
 
int main()
{
    printf("=*1===%d \n", ROUND_UP(0,4));
    printf("=*1===%d \n", ROUND_UP(3,4));
    printf("=*1===%d \n", ROUND_UP(13,4));
    
    printf("=1===%d \n", ROUND_UP_INI(0,4));
     printf("=1===%d \n", ROUND_UP_INI(3,4));
     printf("=1===%d \n", ROUND_UP_INI(4,4));
    printf("=1===%d \n", ROUND_UP_INI(13,4));
    printf("=2===%d \n", ROUND_UP_INI(14,4));
    printf("=3===%d \n", ROUND_UP_INI(15,4));
    printf("=4===%d \n", ROUND_UP_INI(16,4));
    
}