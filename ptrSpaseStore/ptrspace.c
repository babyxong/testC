
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

void main(void)
{
    int *p = NULL;  
    
    void *testp;
	STaaa_t    TesA;
	
	int addr = &TesA;
	
    p = addr;
    
    
     testp = &TesA;
     
     
     printf("=====1=======%p \n", testp);
     printf("=====2=======%p \n", testp+1);
     
    
    STaaaB_t Fk;
    TesA.BBBB = &Fk;
    
    printf("%s","ssdfd==============""sdasdasdxxxxxxxxxxxxxxxxxxxxxxx ");
    
    TesA.BBBB->BA =111;
   
    printf ("2======= *p = %d\n\r", TesA.BBBB->BA);
    
    
}