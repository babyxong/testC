#include <sys/file.h>
  #include <sys/types.h>
       #include <unistd.h>
#include<stdio.h>
#include<stdlib.h>   // exit
#include<fcntl.h>    // O_WRONLY
#include<sys/stat.h>
#include<time.h>     // time
#include<signal.h>
 
       #include <pthread.h>

void test1 (int num) 
{
    printf("%s:%d FIFO broken callback %d !!!.\n",__FUNCTION__,__LINE__,num); // 说明进程ID
}

void BlockSigno(int signo)  /* 阻塞掉某个信号 */
{ 
    sigset_t signal_mask;
    sigemptyset(&signal_mask); /* 初始化信号集,并清除signal_mask中的所有信号 */
    sigaddset(&signal_mask, signo); /* 将signo添加到信号集中 */

 //   sigprocmask(SIG_BLOCK, &signal_mask, NULL); /* 这个进程屏蔽掉signo信号 */

	pthread_sigmask(SIG_BLOCK, &signal_mask, NULL); /* 这个线程屏蔽掉signo信号 */
}

void * pipeWriteTask(void *arg)
{	
	int fd;
    int ret;
	int n, i;
	char buf[1024];
	time_t tp;

	BlockSigno(SIGPIPE);  //线程屏蔽信号

	printf ("pipeWriteTask go");

	if((fd = open("fifo.temp", O_WRONLY)) < 0) // 以写打开一个FIFO 
	{
		perror("Open FIFO Failed");
		exit(1);
	}

	while(1)
	{
		time(&tp);  // 取系统当前时间
		n = sprintf(buf,"Process %d's time is %s",getpid(),ctime(&tp));
		printf("Send message: %s", buf); // 打印        
        
        ret = write(fd, buf, 1024);
		if(ret< 0)  // 写入到FIFO中
		{

			printf("%s:%d", __FUNCTION__,__LINE__);
			perror("Write FIFO Failed");		
		}
		sleep(1);  // 休眠1秒
	}

	return 0;
}

void * pipeWriteTask2(void *arg)
{	
	int fd;
    int ret;
	int n, i;
	char buf[1024];
	time_t tp;

	printf ("pipeWriteTask go");

	///BlockSigno(SIGPIPE);  //线程没有屏蔽信号，会让进程中断

	if((fd = open("fifo.temp", O_WRONLY)) < 0) // 以写打开一个FIFO 
	{
		perror("Open FIFO Failed");
		exit(1);
	}
	
	while(1)
	{
		time(&tp);  // 取系统当前时间
		n = sprintf(buf,"Process %d's time is %s",getpid(),ctime(&tp));
		printf(" pipeWriteTask2 Send message: %s", buf); // 打印        
        
        ret = write(fd, buf, 1024);
		if(ret< 0)  // 写入到FIFO中
		{

			printf("%s:%d", __FUNCTION__,__LINE__);
			perror(" pipeWriteTask2 Write FIFO Failed");		
		}
		sleep(1);  // 休眠1秒
	}

	return 0;
}

int main()
{
	
	printf("I am %d process.\n", getpid()); // 说明进程ID
	
    printf("to open write only .\n");
	

    printf("to open write only over .\n");
 
	pthread_t thrd;
       
	pthread_create(&thrd , NULL ,    pipeWriteTask, NULL);

	pthread_create(&thrd , NULL ,    pipeWriteTask2, NULL);
    //< signal(SIGPIPE, test1);
    
	while (1)
	{
	sleep(1);  // 休眠1秒

	}	
	

	return 0;
}
