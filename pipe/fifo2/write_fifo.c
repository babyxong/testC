#include <sys/file.h>

#include<stdio.h>
#include<stdlib.h>   // exit
#include<fcntl.h>    // O_WRONLY
#include<sys/stat.h>
#include<time.h>     // time
#include<signal.h>
 

void test1 (int num) 
{
    printf("FIFO broken callback %d !!!.\n", num); // 说明进程ID
}
 
int main()
{
	int fd;
    int ret;
	int n, i;
	char buf[1024];
	time_t tp;
 
	printf("I am %d process.\n", getpid()); // 说明进程ID
	
    printf("to open write only .\n");
	if((fd = open("fifo.temp", O_WRONLY)) < 0) // 以写打开一个FIFO 
	{
		perror("Open FIFO Failed");
		exit(1);
	}
    printf("to open write only over .\n");
 
    
    signal(SIGPIPE, test1);
    
	while(1)
	{
		time(&tp);  // 取系统当前时间
		n=sprintf(buf,"Process %d's time is %s",getpid(),ctime(&tp));
		printf("Send message: %s", buf); // 打印
        
        flock(fd, LOCK_EX);
        
        ret = write(fd, buf, 1024);
		if(ret< 0)  // 写入到FIFO中
		{
			perror("Write FIFO Failed");		
		}
		sleep(1);  // 休眠1秒
          flock(fd, LOCK_UN);
	}
 
	close(fd);  // 关闭FIFO文件
	return 0;
}
