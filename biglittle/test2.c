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
static inline int32_t BigLittleSwap(const uint8_t *pSrcData, uint8_t *pDestData, uint32_t srcSize, uint32_t dstSize)
{
    int32_t ret;
	uint32_t i;
	uint8_t  tmp;
	
	if (NULL == pSrcData || NULL == pDestData) {
		printf(" 需要打印日志 ");	
		ret = -1;
	}
 
	for (i = 0; i < (srcSize+1)/2; i++) {
		*(pDestData + srcSize -i -1) = *(pSrcData+i);		
		*(pDestData+i) = *(pSrcData + srcSize -i -1);
	}
	
    for (i = srcSize; i < dstSize; i++) {
        *(pDestData + i) &= 0;
    } 
}

/**
  * @brief  Main program.
  * @param  None.
  * @return None.
  */
int main(void)
{
	uint32_t n =0;

	uint8_t Data1[] ={0x01, 0x02, 0x03, 0x04, 0x05};  
    uint8_t Data2[100]; 
 
	BigLittleSwap(&Data1[0], &Data2[0],  sizeof(Data1), sizeof(Data2));

	for (n =0 ;n< sizeof(Data1);n++)
	{
		printf("swap1 %d = %#lx\n", n,*(Data2+n));
	}
}










