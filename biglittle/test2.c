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
    
    if (dstSize <srcSize ) {
         printf ("=====errr \n");
    }

	for (i = 0; i < (srcSize+1)/2; i++) {
        
        if (srcSize -i -1 > dstSize ||
            srcSize -i -1 < 0 ||
            i > dstSize) 
        {
            break;
            printf ("=====break \n");
        }
        
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

	uint8_t Data1[] ="HELLL....";  
    uint8_t Data2[100]; 
 
	BigLittleSwap(&Data1[0], &Data2[0],  sizeof(Data1), sizeof(Data2));
    
    

	for (n =0 ;n< sizeof(Data1);n++)
	{
		printf("swap1 %d = %#lx\n", n,*(Data2+n));
        printf("data1 %d = %#c\n", n,*(Data1+n));
        printf("data2 %d = %#c\n", n,*(Data2+n));
        printf("==============\n", n,*(Data2+n));
	}
}










