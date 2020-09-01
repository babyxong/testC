/* Header includes -----------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
static void BigAndLittleEndianConversion(void *data, uint32_t size);

/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Big and little endian conversion.
  * @param  [in] data: The pointer of the data to be converted.
  * @param  [in] size: The size of the data to be converted.
  * @return None.
  */
static void BigAndLittleEndianConversion(void *data, uint32_t size)
{
  for(uint32_t i = 1; i < size; i++)
  {
    for(uint32_t j = 1; j < size - i + 1; j++)
    {
      uint8_t c = *(((uint8_t *)data) + j - 1);
      *(((uint8_t *)data) + j - 1) = *(((uint8_t *)data) + j);
      *(((uint8_t *)data) + j) = c;
    }
  }
}

/**
  * @brief  Main program.
  * @param  None.
  * @return None.
  */
int main(void)
{
  char  xxxx = -1;
  unsigned char aaaa = 255;
  printf ("===1===%c \n", (unsigned char)xxxx) ;  
  printf ("===255===%c \n", aaaa) ; 
  
  
  printf ("======%u \n", xxxx) ; 
  printf ("======%#x \n", (uint8_t)xxxx) ;  
  printf ("======%#x \n", 253) ; 

  int32_t  I32A = -1;
  uint32_t U32A = 0xFFFFFFFF;
  
  printf ("===i32===%u \n", I32A) ; 
  printf ("===u32===%u \n", U32A) ;  
  printf ("======%#x \n", 253) ; 
  
  if (I32A == U32A) 
  {
      printf ("wo tmd jinlaile   ===== \n");
  }
    
  if (xxxx == aaaa) 
  {
    printf ("wo buzhidao jinbujinlai  ===== \n");
  }      
    
  if (253 == xxxx) {
      printf ("xiangdeng ===== \n");
  }
  
  
  
  uint64_t bigEndianData             = 0x0123456789ABCDEF;
  
	printf(" bigEndianData size: %u  \n", sizeof(bigEndianData));
  
  BigAndLittleEndianConversion(&bigEndianData, sizeof(bigEndianData));
  

  uint64_t b512    = 512;
  
  
  


	printf("bigEndianData = %#lx\n", bigEndianData);

}