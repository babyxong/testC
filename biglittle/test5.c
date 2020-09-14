/* Header includes -----------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>


#define SWAP16_BIGXLITTLE_V(x) \
    (((uint16_t)(x) & (0xFF << 0)) << 8 |\
     ((uint16_t)(x) & (0xFF << 8)) >> 8)

#define SWAP32_BIGXLITTLE_V(x) \
    ((((uint32_t)(x) & (0xFF <<  0)) << 24) | \
     (((uint32_t)(x) & (0xFF <<  8)) << 8 ) | \
     (((uint32_t)(x) & (0xFF << 16)) >> 8 ) | \
     (((uint32_t)(x) & (0xFF << 24)) >> 24))

#define SWAP64_BIGXLITTLE_V(x) \
    ((((uint64_t)(x) & ((uint64_t)0xFF <<  0)) << 56) |\
     (((uint64_t)(x) & ((uint64_t)0xFF <<  8)) << 40) |\
     (((uint64_t)(x) & ((uint64_t)0xFF << 16)) << 24) |\
     (((uint64_t)(x) & ((uint64_t)0xFF << 24)) << 8)  |\
     (((uint64_t)(x) & ((uint64_t)0xFF << 32)) >> 8)  |\
     (((uint64_t)(x) & ((uint64_t)0xFF << 40)) >> 24) |\
     (((uint64_t)(x) & ((uint64_t)0xFF << 48)) >> 40) |\
     (((uint64_t)(x) & ((uint64_t)0xFF << 56)) >> 56))    
     
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
    uint16_t data16a = 0xfe10;
    printf("=======data16a=======%#X  \n", data16a);
    printf("=======data16a=======%#X  \n", SWAP16_BIGXLITTLE_V(data16a)); 
    
    uint32_t data32a = 0xfe01ab12;
    printf("=======data16a=======%#X  \n", data32a);
    printf("=======data16a=======%#X  \n", SWAP32_BIGXLITTLE_V(data32a)); 
    
    uint64_t data64a = 0x12345678fe01ab12;
    printf("=======data16a=======%#X  \n", data32a);
    printf("=======data16a=======%#X  \n", SWAP64_BIGXLITTLE_V(data32a)); 
    
    
}



//0xFF FF FF FF 
//     FF FF FF FF






