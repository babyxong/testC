
 #include <stdio.h>

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
 
#define BUFFER_SIZE 1025
 
int MAX_LIST = 2;
 
void aio_completion_handler(sigval_t sigval)
{
    //用来获取读aiocb结构的指针
    struct aiocb *prd;
    int ret;
 
    prd = (struct aiocb *)sigval.sival_ptr;
 
    printf("hello1111111111111111\n");
 
    //判断请求是否成功
    if(aio_error(prd) == 0)
    {
        //获取返回值
        ret = aio_return(prd);
        printf("读返回值为:%d\n",ret);
    }
}

void aio_completion_handler2(sigval_t sigval)
{
    //用来获取读aiocb结构的指针
    struct aiocb *prd;
    int ret;
 
    prd = (struct aiocb *)sigval.sival_ptr;
 
    printf("hello222222222222222\n");
 
    //判断请求是否成功
    if(aio_error(prd) == 0)
    {
        //获取返回值
        ret = aio_return(prd);
        printf("读返回值为:%d\n",ret);
    }
}

 
int main(int argc,char **argv)
{
    struct aiocb *listio[3];
    struct aiocb rd,wr, wr2;
    int fd,ret;
 
    //异步读事件
    fd = open("test1.txt",O_RDONLY);
    if(fd < 0)
    {
        perror("test1.txt");
    }
 
    bzero(&rd,sizeof(rd));
 
    rd.aio_buf = (char *)malloc(BUFFER_SIZE);
    if(rd.aio_buf == NULL)
    {
        perror("aio_buf");
    }
 
    rd.aio_fildes = fd;
    rd.aio_nbytes = 1024;
    rd.aio_offset = 0;
    rd.aio_lio_opcode = LIO_READ;   ///lio操作类型为异步读
 
    //将异步读事件添加到list中
    listio[0] = &rd;
 
 
    //异步些事件
    fd = open("test2.txt",O_WRONLY | O_APPEND);
    if(fd < 0)
    {
        perror("test2.txt");
    }
 
    bzero(&wr,sizeof(wr));
 
    wr.aio_buf = (char *)malloc(BUFFER_SIZE);
    if(wr.aio_buf == NULL)
    {
        perror("aio_buf");
    }
 
    wr.aio_fildes = fd;
    wr.aio_nbytes = 1024;
    wr.aio_offset = 0;
    wr.aio_lio_opcode = LIO_WRITE;   ///lio操作类型为异步写
    sprintf((char *)wr.aio_buf, "Xuhong 1 \n");
    
    wr.aio_sigevent.sigev_notify = SIGEV_THREAD;//使用线程回调通知
    wr.aio_sigevent.sigev_notify_function = aio_completion_handler;//设置回调函数
    wr.aio_sigevent.sigev_notify_attributes = NULL;//使用默认属性
    wr.aio_sigevent.sigev_value.sival_ptr = &rd;//在aiocb控制块中加入自己的引用

    wr2.aio_buf = (char *)malloc(BUFFER_SIZE);
    if(wr2.aio_buf == NULL)
    {
        perror("aio_buf");
    }
    wr2.aio_fildes = fd;
    wr2.aio_nbytes = 1024;
    wr2.aio_offset = 1500;
    wr2.aio_lio_opcode = LIO_WRITE;   ///lio操作类型为异步写
    sprintf((char *)wr2.aio_buf, "Xuhong 2 \n");
 
    wr2.aio_sigevent.sigev_notify = SIGEV_THREAD;//使用线程回调通知
    wr2.aio_sigevent.sigev_notify_function = aio_completion_handler2;//设置回调函数
    wr2.aio_sigevent.sigev_notify_attributes = NULL;//使用默认属性
    wr2.aio_sigevent.sigev_value.sival_ptr = &rd;//在aiocb控制块中加入自己的引用
 
    //将异步写事件添加到list中
    listio[1] = &wr;
    listio[2] = &wr2;
    //使用lio_listio发起一系列请求
    ret = lio_listio(LIO_WAIT,listio,3,NULL);
 
    //当异步读写都完成时获取他们的返回值
 
    ret = aio_return(&rd);
    printf("\n读返回值:%d \n",ret);
 
    ret = aio_return(&wr);
    printf("\n写返回值:%d \n",ret);
 
    ret = aio_return(&wr2);
    printf("\n写返回值:%d \n",ret);
    
    
 
    return 0;
}