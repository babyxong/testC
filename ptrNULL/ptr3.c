#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int gAAAA =1;
int gBBBB =2;


struct ST_AB {
    int AP;
    int *pAA;
    
};

void funB(int data)
{
    printf ("==============FunbB .\n") ;
    
}


void funA(int **p)
{
      *p = &gBBBB;
      
      *p = (int*)(void*)funB;
      
      //memcpy(*p -10  ,&gBBBB, sizeof(gBBBB));
      
      *p = 0;
      
      funB(12);
      
}

void main(void)
{
    int *p = NULL;   
    p = &gAAAA;
    
    printf ("gAAAA:%p  gBBBB:%p \n\r", &gAAAA, &gBBBB);
    
    printf ("\n\r");
    printf ("111 &p = %p \n\r", &p);
    printf ("1======= *p = %d\n\r", *p);  
    
    struct ST_AB *pA = malloc(sizeof(struct ST_AB));
    
    memset(pA , 0 , sizeof(struct ST_AB));
    
    printf ("=======pAA:%p \n", pA->pAA) ;
    
    funA(&p);
    
    printf ("222 p = %p \n\r", p);
    
    printf ("2======= *p = %d\n\r", *p);
    
    
}