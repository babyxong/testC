/* Header includes -----------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>


/**
  * @brief  Main program.
  * @param  None.
  * @return None.
  */
#define PLUS_ONE  0x0123
  
int main(void)
{
    int aaa = 1234;
    
  printf ("============= %d \n",PLUS_ONE);
  printf ("============= %#x \n",PLUS_ONE);
  
  
  printf ("========~===== %d \n",~PLUS_ONE);
   printf ("========~===== %#x \n",~PLUS_ONE);
  
    printf ("========~===== %d \n", -PLUS_ONE);
   printf ("========~===== - %#x \n", ~(-PLUS_ONE)+1);
	
    
    printf("============= %d \n",aaa);
    printf("============= %d \n", -aaa);
}