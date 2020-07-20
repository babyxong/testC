/* Header includes -----------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
/* Function definitions ------------------------------------------------------*/


/**
  * @brief  Big and little endian conversion.
  * @param  [in] data: The pointer of the data to be converted.
  * @param  [in] size: The size of the data to be converted.
  * @return None.
  */
static inline void BigLittleSwap( uint8_t *pdata, uint32_t size)
{
	uint32_t i;
	uint32_t j;
	uint8_t  tmp;
 
	for (i = 0; i < (size+1)/2; i++)
	{
		tmp = *(pdata+i);
		*(pdata+i) = *(pdata+size-i-1);
		*(pdata+size-i-1) = tmp;
	}
 
	printf(" pdata: %d \n", *pdata);
  
}

/**
  * @brief  Main program.
  * @param  None.
  * @return None.
  */
int main(void)
{
	uint32_t n =0;

	uint8_t Data1[]={0x01, 0x02, 0x03, 0x04, 0x05};  
 
	BigLittleSwap(&Data1[0], sizeof(Data1));

	for (n =0 ;n< sizeof(Data1);n++)
	{
		printf("swap1 %d = %#lx\n", n,*(Data1+n));
	}
	
	BigLittleSwap(&Data1[0], sizeof(Data1));
	for (n =0 ;n< sizeof(Data1);n++)
	{
		printf("swap2 %d = %#lx\n", n,*(Data1+n));
	}
	
	uint64_t udata = 0x0123456789ABCDEF;
	
	BigLittleSwap((uint8_t *)&udata, sizeof(udata));
	printf("sizeof : %u \n", sizeof(udata));
	printf("bigEndianData %#lx \n ", udata);
	
	

}