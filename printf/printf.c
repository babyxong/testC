
#include <stdio.h>

char asc[] = "     ";

int aaa(int * pa)
{
    unsigned int testA[1000] = {0};
    (void)pa;
    
    return 1;
}

void main(void)
{
    unsigned long long Au64 =100;
    long long          As64 =100;
    
    unsigned int   a = -1;
    int b;
    
///   printf ("==%llu=======%llu \n", Au64, 12);
///
///    printf ("==%llu=======%llu \n", asc[0], asc[1]);
///   
///   printf ("=========%lld \n", Au64);
///    printf ("=========%lld \n", As64);
    printf ("=========%lld \n", As64);
     
    unsigned int testA[1000] = {0};
     
//     printf ("\t =\t=88888888=======%lld \n", Au64);

//    printf ("\t =\t=2222222222222222=======%d \n", -(a));
//    printf ("\t =\t=2222222222222222=======%#x \n", -(a));
     printf("==%s ===%s", __DATE__, __TIME__);
     
      aaa(&b);
}
