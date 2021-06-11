#include <stdio.h>

int main(int argc, char *argv[])
{
                 char buf[1024];
                 FILE *pp;

                              //r表示返回的指针是可读的。
                 if( (pp = popen("ls", "r")) == NULL )
                 {
                         printf("popen() error!\n");
                         return 0 ;
                 }

         while(fgets(buf, sizeof buf, pp))
                 {
                         printf("%s", buf);
                 }
                 pclose(pp);
                 return 0;
}


sh  ls > pp 