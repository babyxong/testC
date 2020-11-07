#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main()
{

   FILE *fp;
    int ret ;
   char text[]="this is a test!";

   //ret = remove("temp");
   //perror("remover");
   //printf("removew ret:%d\n", ret);

   while(1) {
        if((fp = fopen("temp", "a+")) == 0)
        {
            printf("can't open file!\n");
        }
   else
   {
      printf("open file success!\n");
      
      ret = fwrite(text, strlen(text), 1, fp);
      printf("fwrite ret: %d \n", ret);
      fclose(fp);
      sleep(3);
      #if 0
        int  i = flock(fileno(fp), LOCK_SH | LOCK_NB); // 加锁以判断文件是否已经被加锁了

        printf("%d\n", i);

        flock(fileno(fp), LOCK_UN);

        fwrite(text, strlen(text), 1, fp);
       #endif
   }


   
   }
   return 0;

}