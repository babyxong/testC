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
  
  uint64_t bigEndianData             = 0x0123456789ABCDEF;
  
	printf(" bigEndianData size: %u  \n", sizeof(bigEndianData));
  
  BigAndLittleEndianConversion(&bigEndianData, sizeof(bigEndianData));
  

  uint64_t b512    = 512;
  
  


	printf("bigEndianData = %#lx\n", bigEndianData);

}