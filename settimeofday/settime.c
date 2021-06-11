
#include <stdio.h>
#include <sys/time.h>

char asc[] = "     ";



void main(void)
{
    struct timeval tv = {0};
    int ret;
    
    ret = settimeofday(&tv, NULL);
    
    
    printf("===========ret :%d\n", ret);
    
    perror("Error: ");    
    
}