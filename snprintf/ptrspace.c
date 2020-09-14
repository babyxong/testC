#include <string.h>
#include <stdio.h>

#define  TESTSTR "Adm +++++ =====!"

void TestPtr (void **p , void *inp)
{
    *p = inp;
    *(p+1) = inp;
}

void main(void)
{
    int *p = NULL;  
    unsigned int ops =0;
    
    
    char buff[1024] ;
    ops = 0;
    ops += snprintf (buff, 1024 - ops , TESTSTR  );
    
    printf("size:%u  ops:%u,  buff:%s \n", sizeof(TESTSTR), ops,buff);
    
    ops = 0;
    ops += sprintf (buff, TESTSTR);
    printf("size:%u  ops:%u,  buff:%s \n", sizeof(TESTSTR), ops,buff);
    
}