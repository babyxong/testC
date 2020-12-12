#include <stdio.h>

#define TRUE 1
#define FLASE 0

#define IS_SIGNED_NUM(a)      (a < 0 ? TRUE :( a =~a,a < 0 ? (a=~a,TRUE):(a=~a,FLASE)))
#define IS_UNSIGNED_NUM(a)  (a >=0 && (a=~a,a >=0 ? (a=~a,TRUE):(a=~a,FLASE)))

void main()
{
    int a1 = 0xffff0001;
    int a2 = 0x0fff0001;
    int a =0;
    unsigned int b1 = 0xffff0001;
    unsigned int b2 = 0xffff0001;
    unsigned int b =0;
   
    char   c =1;
    unsigned char c1= 2;
    
    
    printf("====is signed : %d=============\n", IS_SIGNED_NUM(a1) );
    printf("====is signed : %d=============\n", IS_SIGNED_NUM(a2) );
    printf("====is signed : %d=============\n", IS_SIGNED_NUM(a) );
    printf("====is signed : %d=============\n", IS_SIGNED_NUM(b1) );
    printf("====is signed : %d=============\n", IS_SIGNED_NUM(b2) );
    printf("====is signed : %d=============\n", IS_SIGNED_NUM(b) );
    
        printf("====is signed c: %d=============\n", IS_SIGNED_NUM(c) );
        
            printf("====is signed c: %d=============\n", IS_SIGNED_NUM(c1) );
}