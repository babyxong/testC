





#include <stdio.h>
#include <stdint.h>

typedef struct info {
    
  int (*funP) (uint32_t arg);
     
}info_t;

typedef struct SCSIBusInfo {
    
    uint32_t num;
    const int tcq;
     int const*p, max_target, max_lun;
    
     int (*parse_cdb) (uint32_t arg);
     
    const info_t info;
}SCSIBusInfo_t;

int func(uint32_t aaa)
{
    printf ("==================%u \n", aaa);
}

int funa(uint32_t aaa)
{
    printf ("//////////////////////%u \n", aaa);
}
int main(void)
{
   uint32_t Mb = 22;
  uint32_t Ma = 21;
   const uint32_t *p;
  p = &Mb;
  
  SCSIBusInfo_t st = {
      .parse_cdb = funa,
      .p = &Ma,
      .tcq = 120,      
      .info.funP = funa,
  };
  
  st.p = &Mb;
  st.num = 0;
  st.num ++;
  
  st.parse_cdb = func;
 
  st.parse_cdb(22222);
  st.info.funP(33333);
  
 
  printf("====%u \n",st.num);
}