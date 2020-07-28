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
    
    
  printf ("============= %d \n",PLUS_ONE);
  printf ("============= %#x \n",PLUS_ONE);
  
  
  printf ("========~===== %d \n",~PLUS_ONE);
   printf ("========~===== %#x \n",~PLUS_ONE);
  
    printf ("========~===== %d \n", -PLUS_ONE);
   printf ("========~===== - %#x \n", ~(-PLUS_ONE)+1);
	

}