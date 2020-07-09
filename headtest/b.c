#include "com.h"
#include <stdio.h>

//extern int gTest;

void Funb()
{
     gTest = 2;
     printf ("B============%p  gTest:%d \n",&gTest,gTest);
}