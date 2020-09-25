#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<aio.h>
#include<unistd.h>
#include<signal.h>

#define BUFFER_SIZE 1024

int gCnt =0;

void aio_callback(sigval_t sigval)
{
       gCnt--;
       printf("\n\n  gCnt = :%d  \n", gCnt);
}

void aio_callbackRead(sigval_t sigval)
{
       char *p = ((struct aiocb*)sigval.sival_ptr)->aio_buf ;
       printf("=====%s\n", p);
}

void aioFun(int size, int  offset) 
{

    int fd,ret,couter;
    static int  times = 0;   
    struct aiocb rd;
    struct aiocb rd2;

    fd = open("test.txt", O_RDWR);
    if(fd < 0)
    {
        perror("test.txt");
    }
    
    //将rd结构体清空
    bzero(&rd, sizeof(rd));
    bzero(&rd2, sizeof(rd2));

    //为rd.aio_buf分配空间
    rd.aio_buf = malloc(BUFFER_SIZE + 1);
    
    sprintf(rd.aio_buf, "The format string is a character string, beginning and ending in its initial shift state, if any  which are copied unchanged to the output stream; and conversion specifications, each of which results in fetching z The format string is a character string, beginning and ending in its initial shift state, if any.  The format string is composed of zero or more directives:ordinary characters (not ), which are copied unchanged to the output stream; and conversion specifications, each of whi  conversion specifications, each of which results in fetching z The format string which are copied unchanged");

    //填充rd结构体
    rd.aio_fildes = fd;
    rd.aio_nbytes = BUFFER_SIZE;
    rd.aio_offset = offset;

     //填充aiocb中有关回调通知的结构体sigevent
    rd.aio_sigevent.sigev_notify = SIGEV_THREAD;//使用线程回调通知
    rd.aio_sigevent.sigev_notify_function = aio_callback;//设置回调函数
    rd.aio_sigevent.sigev_notify_attributes = NULL;//使用默认属性
    rd.aio_sigevent.sigev_value.sival_ptr = &rd;//在aiocb控制块中加入自己的引用

    gCnt ++;
    //进行异步读操作
    ret = aio_write(&rd);
    if(ret < 0)
    {
        perror("aio_write");
    }  
    

    
    rd2.aio_buf = malloc(BUFFER_SIZE + 1);
    
    rd2.aio_fildes = fd;
    rd2.aio_nbytes = BUFFER_SIZE;
    rd2.aio_offset = offset;
    
     //填充aiocb中有关回调通知的结构体sigevent
    rd2.aio_sigevent.sigev_notify = SIGEV_THREAD;//使用线程回调通知
    rd2.aio_sigevent.sigev_notify_function = aio_callbackRead;//设置回调函数
    rd2.aio_sigevent.sigev_notify_attributes = NULL;//使用默认属性
    rd2.aio_sigevent.sigev_value.sival_ptr = &rd2;//在aiocb控制块中加入自己的引用
    
    ret = aio_read(&rd2);
    if(ret < 0)
    {
        perror("aio_read");
    }  
    
    while(1){
          
    }
    
	//do other things
	
    couter = 0;
//  循环等待异步读操作结束
    #if 1
    while(aio_error(&rd) == EINPROGRESS)
    {
       // printf("第%d次\n",++couter);
    }
	#endif
    //获取异步读返回值
    ret = aio_return(&rd);
	
    printf("\n\ntimes: %d 返回值为:%d    \n", times,ret);
	printf("%s\n",rd.aio_buf);
	
	free((void *)rd.aio_buf);
	close(fd);

    times++;
}

int main(int argc,char **argv)
{
    //aio操作所需结构体
    
    
   aioFun( 2,   0) ;
   
   aioFun( 2,   4) ;
   
   while (1)
   {

    
   }
  
    return 0;
}
