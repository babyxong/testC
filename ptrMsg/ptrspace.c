
#include <stdio.h>

int gAAAA =1;
int gBBBB =2;


typedef struct STaaaB{
    char *BA;
}stSTA;

void funA(stSTA *AB )
{
    printf("==funA===%p \n", AB);
    printf("==funA===%p \n", &(AB->BA));
    printf("==funA===%d \n", *(AB->BA));
}


void main(void)

{
    int *p = NULL;  


    
    char Pt = 25;
    char *Pa;
    
    Pa = &Pt;
    
    stSTA AK;
    
    AK.BA = &Pt;
    
    printf("====AK====%p \n", &AK);
    printf("====AK.BA=%p \n", &(AK.BA));
    
    funA(&AK);
    
    
    printf("%s","ssdfd==============""sdasdasdxxxxxxxxxxxxxxxxxxxxxxx ");
    
    
    
}