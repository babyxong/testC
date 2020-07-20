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


#define BUFFER_SIZE 1024

int MAX_LIST = 2;

int main(int argc,char **argv)
{
    //aio操作所需结构体
    struct aiocb rd,wd;

    int fd1,fd2,ret,couter;

    //cblist链表
    const struct aiocb *aiocb_list[2];

    fd1 = open("test1.txt",O_RDONLY);
    if(fd1 < 0)
    {
        perror("test1.txt");
    }
 
	fd2 = open("test2.txt",O_WRONLY | O_APPEND);
    if(fd2 < 0)
    {
        perror("test2.txt");
    }
	
	
    //将rd结构体清空
    bzero(&rd,sizeof(rd));


    //为rd.aio_buf分配空间
    rd.aio_buf = malloc(BUFFER_SIZE + 1);

    //填充rd结构体
    rd.aio_fildes = fd1;
    rd.aio_nbytes =  BUFFER_SIZE;
    rd.aio_offset = 0;

    //将读fd的事件注册
    aiocb_list[0] = &rd;

    //进行异步读操作
    ret = aio_read(&rd);
    if(ret < 0)
    {
        perror("aio_read");
        exit(1);
    }
	
	//将rd结构体清空
    bzero(&wd,sizeof(rd));


    //为rd.aio_buf分配空间
    wd.aio_buf = malloc(BUFFER_SIZE + 1);

    //填充rd结构体
    wd.aio_fildes = fd2;
    wd.aio_nbytes =  BUFFER_SIZE;


    //将读fd的事件注册
    aiocb_list[1] = &wd;

    //进行异步写操作
    ret = aio_write(&wd);
    if(ret < 0)
    {
        perror("aio_write");
        exit(1);
    }

    printf("我要开始等待异步读事件完成 start \n");
    //阻塞等待异步读事件完成
    ret = aio_suspend(aiocb_list, MAX_LIST,NULL);
    printf("我要开始等待异步读事件完成 end , ret :%d \n", ret);
	
    //获取异步读返回值
    ret = aio_return(&rd);
	
	printf("读取完成： \n%s\n",rd.aio_buf);

    printf("\n\nrd返回值为:%d\n",ret);
	
	ret = aio_return(&wd);

    printf("\n\nwd返回值为:%d\n",ret);


    return 0;
}
