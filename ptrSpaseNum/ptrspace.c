#include <string.h>
#include <stdio.h>

int gAAAA =1;
int gBBBB =2;

void funA(int **p)
{
      *p = &gBBBB;
}


typedef struct STaaaB{
    char BA;
}STaaaB_t;

typedef struct STaaa{
    
    STaaaB_t *BBBB;
    char * AA;
    char A;
}STaaa_t;



void TestPtr (void **p , void *inp)
{
    *p = inp;
    *(p+1) = inp;
}

void main(void)
{
    int *p = NULL;  

    void *ptr[3];
    
    ptr[0] = &gAAAA;
    
    printf ("prt 0 = %p    \n", ptr[0]);
    
    
    ptr[1] = &gBBBB;
    printf ("prt 0 = %p    \n", ptr[1]);
    
    memset(&ptr, 0 , sizeof(ptr));  
    
    
    
    printf ("===============%d   == \n", sizeof(ptr));
    printf ("prt 0 = %p    \n", ptr[0]);
    printf ("prt 0 = %p    \n", ptr[1]);
    
    TestPtr(&ptr[0], TestPtr);
    printf ("======= TO ====== \n");
    printf ("fun 0 = %p    \n", TestPtr);
    
    printf ("prt 0 = %p    \n", ptr[0]);
    printf ("prt 0 = %p    \n", ptr[1]);
    
    STaaa_t    TesA;
    
    STaaaB_t Fk;
    TesA.BBBB = &Fk;
    
    printf("%s","ssdfd==============""sdasdasdxxxxxxxxxxxxxxxxxxxxxxx \n");
    
    TesA.BBBB->BA =111;
   
    printf ("2======= *p = %d\n\r", TesA.BBBB->BA);
    
    
}