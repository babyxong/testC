/* Header includes -----------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>


#define SWAP16_BIGXLITTLE(px) \
    ((*(uint16_t*)px & (0xFF << 0)) << 8 |\
     (*(uint16_t*)px & (0xFF << 8)) >> 8)

#define SWAP32_BIGXLITTLE(px) \
    (((*(uint32_t*)px & (0xFF <<  0)) << 24) | \
     ((*(uint32_t*)px & (0xFF <<  8)) << 8 ) | \
     ((*(uint32_t*)px & (0xFF << 16)) >> 8 ) | \
     ((*(uint32_t*)px & (0xFF << 24)) >> 24))

#define SWAP64_BIGXLITTLE(px) \
    (((*(uint64_t*)px & ((uint64_t)0xFF <<  0)) << 56) |\
     ((*(uint64_t*)px & ((uint64_t)0xFF <<  8)) << 40) |\
     ((*(uint64_t*)px & ((uint64_t)0xFF << 16)) << 24) |\
     ((*(uint64_t*)px & ((uint64_t)0xFF << 24)) << 8)  |\
     ((*(uint64_t*)px & ((uint64_t)0xFF << 32)) >> 8)  |\
     ((*(uint64_t*)px & ((uint64_t)0xFF << 40)) >> 24) |\
     ((*(uint64_t*)px & ((uint64_t)0xFF << 48)) >> 40) |\
     ((*(uint64_t*)px & ((uint64_t)0xFF << 56)) >> 56))    
     
#define SWAP16_BIG2LITTLE(pX)   SWAP16_BIGXLITTLE(pX)
#define SWAP16_LITTLE2BIG(pX)   SWAP16_BIGXLITTLE(pX)
#define SWAP32_BIG2LITTLE(pX)   SWAP32_BIGXLITTLE(pX)
#define SWAP32_LITTLE2BIG(pX)   SWAP32_BIGXLITTLE(pX)
#define SWAP64_BIG2LITTLE(pX)   SWAP64_BIGXLITTLE(pX)
#define SWAP64_LITTLE2BIG(pX)   SWAP64_BIGXLITTLE(pX)     
/**
  * @brief  Main program.
  * @param  None.
  * @return None.
  */
int main(void)
{
	uint32_t n =0;
    
	uint8_t Data1[] ={0xA1,0x02};  
    uint16_t data = SWAP16_BIG2LITTLE(Data1);
    printf("==============%p  %p\n", Data1 , Data1+1);
    
    printf("==============%#X  \n", *(uint16_t*)Data1);
	printf("==============%#X  \n", data);
    
    uint8_t Data2[] ={0xA1,0xB2,0xC3,0xD4};  
    uint32_t data2 = SWAP32_BIG2LITTLE(Data2);
     printf("==============%p  %p\n", Data2 , Data2+1);
    
    printf("==============%#X  \n", *(uint32_t*)Data2);
	printf("==============%#X  \n", data2);
    
    uint8_t Data3[] ={0xA1,0xB2,0xC3,0xD4, 0x01, 0x02, 0x03, 0x04};  
    uint64_t data3 = SWAP64_BIG2LITTLE(Data3);
    
    printf("=======Data3=======%#lX  \n", *(uint64_t*)Data3);
	printf("=======data3=======%#lX  \n", data3);
    
    printf("==============%#lX  \n", Data3[0]<<56);
    
    uint64_t test4 = 0x12345678;
    uint8_t Data4[4];
    
    *(uint32_t *)Data4 = SWAP32_LITTLE2BIG(&test4);
    
    printf("=======test4=======%#lX  \n",test4);
    printf("=======Data4=======%#lX  \n", *(uint32_t *)Data4);
    
    
    
}



//0xFF FF FF FF 
//     FF FF FF FF






