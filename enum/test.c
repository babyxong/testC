#include <stdio.h>

#define TRUE 1
#define FLASE 0

#define IS_SIGNED_NUM(a)      (a < 0 ? TRUE :( a =~a,a < 0 ? (a=~a,TRUE):(a=~a,FLASE)))
#define IS_UNSIGNED_NUM(a)  (a >=0 && (a=~a,a >=0 ? (a=~a,TRUE):(a=~a,FLASE)))

typedef enum EnChar {
        Cn1 = 0x1,
}EnChar_e;

typedef enum EnInt{
         In1 = 0x0101,
}EnInt_e;

typedef enum EnLong{
        Ln1 = 0x0101,
}EnLong_e;

typedef enum EnFloat{
         Fn = 0x0101010101
}EnFloat_e;

typedef enum EnDouble{
         Dn1 = 0xfffffffffff
}EnDouble_e;

void main()
{    
    EnChar_e *p1;
    EnDouble_e *p2;

    printf("===EnChar_e=is signed : %d=============\n", sizeof(EnChar_e) );
    printf("===EnInt_e=is signed : %d=============\n", sizeof(EnInt_e) );
    printf("===EnLong_e=is signed : %d=============\n", sizeof(EnLong_e) );
    printf("===EnFloat_e=is signed : %d=============\n", sizeof(EnFloat_e) );
    printf("===EnDouble_e=is signed : %d=============\n", sizeof(EnDouble_e) );
    printf("====is signed : %d=============\n", sizeof(EnChar_e)  );
    
    printf ("=1==1 %p===2 %p=====\n", p1, p1+1) ;

    printf ("=2==1 %p===2 %p=====\n", p2, p2+1) ;
}