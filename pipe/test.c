
#include <sys/types.h>  
#include <unistd.h>  
#include <stdio.h>
#include <fcntl.h>
#include <string.h> 
#include <errno.h>
#include <stdlib.h>
 
#define MAXLEN 100
 
void client(int readfd,int writefd);
void server(int readfd,int writefd);
  
int main(int argc,char* argv)  
{  
  
    int pipe1[2],pipe2[2];  
  
    pid_t childpid;  
  
    pipe(pipe1);  
  
    pipe(pipe2);/*父进程首先创建两个 pipes*/  
  
    if(childpid = fork() == 0)/*父进程fork出子进程，子进程也携带有两个pipes*/  
  
    {  
  
        close(pipe1[1]);/*子进程关闭pipe1的写 与 pipe2的读*/  
  
        close(pipe2[0]);  
  
        server(pipe1[0],pipe2[1]);/*子进程运行server 程序*/  
  
        exit(0);/*子进程终止，变成僵尸进程，*/  
  
    }  
  
    close(pipe1[0]);/*父进程关闭pipe1的读 与 pipe2的写*/  
  
    close(pipe2[1]);  
  
    client(pipe2[0],pipe1[1]);/*父进程运行client 程序*/  
  
    waitpid(childpid,NULL,0);/*父进程等待子进程结束，取得已终止的子进程（僵尸进程）的终止状态。 
                            若无waitpid,则子进程将托孤给Init进程，最终由init进程取得僵尸子进程的状态。*/  
  
    exit(0);  
  
}  
 
 
void client(int readfd,int writefd)/*参数分别为 pipe2[0],pipe1[1]*/ 
{  
  
    size_t len;  
  
    ssize_t n;  
  
    char buff[MAXLEN];  
  
    fgets(buff,MAXLEN,stdin);/*从标准输入stdin中获取输入（一段路径名）放入buff*/  
  
    len = strlen(buff);  
  
    if(buff[len - 1] == '\n') /*删除由fgets存入的换行符*/  
    {
        len--;  
    }
    write(writefd,buff,len);/*将buff中内容写入管道pipe1[1] writefd，传输到子进程server*/  
  
    while((n = read(readfd,buff,MAXLEN)) > 0)/*从pipe[0] readfd中读取子进程server传输过来的内容放入buff，并显示到标准输出stdout*/  
    {
        buff[MAXLEN-1] ='\0';
       
        write(STDOUT_FILENO,buff,n);  
    }
}  
 
void server(int readfd,int writefd)/*参数对应pipe1[0],pipe2[1]*/
{  
  
    int fd;  
  
    ssize_t n;  
  
    char buff[MAXLEN+1];  
  
    if((n = read(readfd,buff,MAXLEN)) == 0)/*从管道pipe1[0] readfd中读取来自父进程client的输入并放入buff*/  
  
        printf("end-of-file while reading pathname\n");  
  
    buff[n] = '\n';  
	buff[MAXLEN] ='\0';
    if((fd = open(buff,O_RDONLY)) < 0)/*open 打开client 通过管道传输过来的路径名*/    
    {  
  
        snprintf(buff+n,sizeof(buff) - n,"can not open %s\n",strerror(errno));  
  
        n=strlen(buff);  
  
        write(writefd,buff,n);/*打开失败，将错误信息写入管道writefd pipe2[1]，传输至父进程client*/    
    }    
    else    
    {  
  
        while((n = read(fd,buff,MAXLEN)) > 0)/*打开成功，将路径名对应的文件中的内容读出到buff， 
 
                                               并写到管道writefd pipe2[1] 传输至父进程client */  
  
        write(writefd,buff,n);  
  
        close(fd);  
  
    }  
}
