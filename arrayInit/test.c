/* Header includes -----------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/**
  * @brief  Main program.
  * @param  None.
  * @return None.
  */
#define PLUS_ONE  0x0123
  
  
/*
若 int a[5]={0}; 则意味bai着a数组的du五个元素都为0，即0 0 0 0 0 ；
若 int a[5]={1}; 则意味着a数组的第一个元素值zhi为dao1，其余元素值为0，即1 0 0 0 0；
若 int a[5]={1,2}; 则意味着a数组的第一个元素为1，第二个元素为2，其余为0，即1 2 0 0 0；
若 int a[5]={1,0,2}; 则意味着a内存储的是1 0 2 0 0；
若 int a[5]; 则意味着a内存储的是随机垃圾值。
*/  
uint8_t   arr1[8] = {0};
uint8_t   arr2[8] = {1}; 

void fun(void)
{
   uint8_t test[20];
   uint8_t test1[223];
   memcpy(test, test1, 1024*1024*10);
}

int main(void)
{
    fun();
   
}
