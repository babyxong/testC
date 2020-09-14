
#include <stdio.h>

int gAAAA =1;
int gBBBB =2;

void funA(int **p)
{
      *p = &gBBBB;
}

void main(void)
{
    int *p = NULL;   
    p = &gAAAA;
    
    printf ("gAAAA:%p  gBBBB:%p \n\r", &gAAAA, &gBBBB);
    
    printf ("\n\r");
    printf ("111 &p = %p \n\r", &p);
    printf ("1======= *p = %d\n\r", *p);  
    
    
    funA(&p);
    
    printf ("222 p = %p \n\r", p);
    
    printf ("2======= *p = %d\n\r", *p);
    
    
}