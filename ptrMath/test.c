





#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
uint32_t *gptr;


uint32_t fun(uint32_t *pMa)
{
    
    *pMa *= 1000;
}

int main(void)
{
  
  uint32_t Ma = 21;
  fun(&Ma);
  uint32_t i;
  
  gptr = (uint32_t *)malloc(sizeof(uint32_t)*10);
  
  for (i =0; i < 10; i++) {
      *(gptr + i) =i;      
  }
  for (i =0; i < 10; i++) {
     printf("printf i:%u ptr %u addr %p \n", i, *(gptr + i), gptr +i);
  }
  
  
  
  printf("11111====%p \n", gptr);
  printf("*****====%u \n", gptr[1]); ///< 此处是取值
  printf("*****====%p \n", &gptr[1]);
  
  printf("22222====%p \n",  (unsigned char * )&gptr[1]);
  printf("33333====%u \n", *(unsigned char * )&gptr[1]);
  
  
  printf("====%u \n",Ma);
  
  
  double A = 123;
  double B = 456;
  
  double C  = 789;
  
  A /= B/C;
  
  
  printf ("===== INT64_C(c) ======%d \n ",  INT64_C(1)<<10 ) ;
  
  printf("====%f \n",A);
  
  printf("====%f \n",A);
}