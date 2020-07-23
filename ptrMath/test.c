





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
}