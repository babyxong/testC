#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
 #include <sys/file.h>

       #include <signal.h>


void pbrokePipe(int unm)
{
    printf("broken pipe ===%d===\n", unm);
}

int main()
{
	int fd;
	int len;
	char buf[1024];
    
    signal(SIGPIPE, pbrokePipe);   
 
	if(mkfifo("fifo.temp", 0666) < 0 && errno!=EEXIST) // 创建FIFO管道
		perror("Create FIFO Failed");
 
	if((fd = open("fifo.temp", O_RDONLY)) < 0)  // 以读打开FIFO
	{
		perror("Open FIFO Failed");
		exit(1);
	}
    
    while (1)
    {
	
        len = read(fd, buf, 1024) ;// 读取FIFO管道4
		printf("Read len:%d ============ message: %s", len,buf);
        int  i = -1;
        while(i <0)
        { 
         i = flock(fd, LOCK_SH | LOCK_NB); // 
         printf("flock:====%d \n", i);
        }
         
    }
    
	close(fd);  // 关闭FIFO文件
	return 0;
}