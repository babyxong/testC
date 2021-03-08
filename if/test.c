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

struct xuhongSt {
    unsigned int a:1;
    unsigned int b:7;
    
    unsigned int c ;
};

//union wy
//{
//     struct
//     {
//          unsigned char x1:2;
//          unsigned char x2:2;
//          unsigned char x3:2;
//          unsigned char x4:2;
//     }cn;
//     unsigned char s;
//} tmp;

void fun(void)
{
    
}

int main()
{
    char * pchar;
    
    char aaaa;
    
    int *p;
    
    p = malloc (100);
    
    char au;

   unsigned int aaa=0xffffffff;
    unsigned int bbb =6;
    
    struct xuhongSt testSt;
    
    memset(&testSt, 0xff, 2);
    
    printf("====testSt size %u \n", sizeof(testSt));
    
    printf("====testSt &a  %p \n", &testSt);
 //   printf("====testSt &a  %p \n", &testSt.a);
 //   printf("====testSt &b  %p \n", &testSt.b);
    printf("====testSt &c  %p \n", &testSt.c);

    printf("====testSt a  %#x \n", testSt.a);
    printf("====testSt b  %#x \n", testSt.b);
    printf("====testSt c  %#x \n", testSt.c);
    
 //   tmp.s = 174;                           //二进制形式是10101110
 //    printf("tmp.s is %d\n",tmp.s);
 //    printf("x1 is %d\n",tmp.cn.x1);
 //    printf("x2 is %d\n",tmp.cn.x2);
 //    printf("x3 is %d\n",tmp.cn.x3);
 //    printf("x4 is %d\n",tmp.cn.x4);

    
}
