#include <sys/file.h>

#include <stdio.h>

#include <stdlib.h>

 

int main()

{

    FILE *f = fopen("temp", "w+");
    int ret;
    
    if(!f)

    {

        printf("error file\n");

        return 0;

    }
    ret = flock(fileno(f), LOCK_EX);
    if(0 == ret)
    {

        printf("lock...\n");

        getchar();

        fclose(f);

        flock(fileno(f), LOCK_UN);

    }
    else
    {

        printf("lock failed ,ret:%d\n", ret);
         perror("flock:");

    }

            return 0;

}