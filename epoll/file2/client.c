#include  <unistd.h>
#include  <sys/types.h>       /* basic system data types */
#include  <sys/socket.h>      /* basic socket definitions */
#include  <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include  <arpa/inet.h>       /* inet(3) functions */
#include <sys/epoll.h> /* epoll function */
#include <fcntl.h>     /* nonblocking */
#include <sys/resource.h> /*setrlimit */
 #include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>


#define MAXEPOLLSIZE 10000
#define MAXLINE 10240
int handle(int connfd);
int setnonblocking(int sockfd)
{
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
        return -1;
    }
    return 0;
}

void *thrdFun(void *arg)
{
    int  servPort = 6888;
    int listenq = 1024;
    long int  ret;
    int listenfd, connfd, kdpfd, nfds, n, nread, curfds,acceptCount = 0;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t socklen = sizeof(struct sockaddr_in);
    struct epoll_event ev;
    struct epoll_event events[MAXEPOLLSIZE];
    struct rlimit rt;
    char buf[MAXLINE] = {0};
        int filefd;
   if(mkfifo("fifo2.temp", 0666) < 0 && errno!=EEXIST) // 创建FIFO管道
		perror("Create FIFO Failed");
    if((filefd = open("fifo2.temp", O_RDONLY | O_NONBLOCK)) < 0)  // 以读打开FIFO
	{
		perror("Open FIFO Failed");
		exit(1);
	}
    
    kdpfd = epoll_create(MAXEPOLLSIZE);   
    
    ev.events = EPOLLIN | EPOLLET |EPOLLERR;
    ev.data.fd = filefd;
    
    if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, filefd, &ev) < 0) 
    {
        fprintf(stderr, "epoll set insertion error: fd=%d\n", listenfd);
        return 0;
    }
    
    printf("reg 2 events %#x %d ------------------\n", ev.events, __LINE__);
    
     for (;;) {
        /* 等待有事件发生 */
        nfds = epoll_wait(kdpfd, events, MAXEPOLLSIZE, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            continue;
        }
        /* 处理所有事件 */
        for (n = 0; n < nfds; ++n)
        {           
            if (events[n].data.fd == filefd) 
            {
                printf("fifo2 event:2131231231231232\n");
                
                ret = read(filefd, buf, 10);
                if(0>ret) 
                {
                    perror("write");
                }
                
                printf("fifo2 event:%#X eventnum:%d n:%d fd:%d ret%d %s \n",events[n].events, nfds, n, filefd , ret, buf);
              
                printf ("============complete \n") ;
            }
        }
    } 
}


int main(int argc, char **argv)
{
    int  servPort = 6888;
    int listenq = 1024;
    long int  ret;
    int listenfd, connfd, kdpfd, nfds, n, nread, curfds,acceptCount = 0;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t socklen = sizeof(struct sockaddr_in);
    struct epoll_event ev;
    struct epoll_event events[MAXEPOLLSIZE];
    struct rlimit rt;
    char buf[MAXLINE] = {0};

    pthread_t tid1;
    ret = pthread_create(&tid1,NULL,thrdFun,NULL);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
    
    int filefd;
   
    if(mkfifo("fifo.temp", 0666) < 0 && errno!=EEXIST) // 创建FIFO管道
		perror("Create FIFO Failed");
    if((filefd = open("fifo.temp", O_RDONLY | O_NONBLOCK)) < 0)  // 以读打开FIFO
	{
		perror("Open FIFO Failed");
		exit(1);
	}    

    kdpfd = epoll_create(MAXEPOLLSIZE);   
    
    // 管道FD -----------------------    
    
    ev.events = EPOLLIN | EPOLLET |EPOLLERR;
    ev.data.fd = filefd;
    
    printf("reg 1 events %#x ------------------\n", ev.events);
    
    if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, filefd, &ev) < 0) 
    {
        fprintf(stderr, "epoll set insertion error: fd=%d\n", listenfd);
        return -1;
    }
    //管道FD-----------------------
    printf("fifo 1file to wait !!!\n");

    for (;;) {
        /* 等待有事件发生 */
        nfds = epoll_wait(kdpfd, events, MAXEPOLLSIZE, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            continue;
        }
        /* 处理所有事件 */
        for (n = 0; n < nfds; ++n)
        {           
            if (events[n].data.fd == filefd) 
            {
                ret = read(filefd, buf, 50);
                if(0>ret) 
                {
                    perror("write");
                }
                
          printf("fifo event:%#X eventnum:%d n:%d fd:%d ret%d %s \n",events[n].events, nfds, n, filefd , ret, buf);
                memset(buf, 0, MAXLINE);
                printf ("============complete \n") ;
            }
        }
    }
   
    return 0;
}
