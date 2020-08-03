





#include <stdio.h>
#include <stdint.h>


uint32_t fun(uint32_t *pMa)
{
    
    *pMa *= 1000;
}

int main(void)
{
  
  uint32_t Ma = 21;
  fun(&Ma);
  
  
  printf("====%u \n",Ma);
  
  
  double A = 123;
  double B = 456;
  
  double C  = 789;
  
  A /= B/C;
  
  
  printf ("===== INT64_C(c) ======%d \n ",  INT64_C(1)<<10 ) ;
  
  printf("====%f \n",A);
  
  printf("====%f \n",A);
}