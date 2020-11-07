
#include <stdio.h>
#include <sys/stat.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


int gFd;
int main()
{
    int ret = mkfifo("./CFIFO", 0664);
    if(ret < 0)
    {
        perror("mkfifo");
        return 0;
    }
    //open
    //read
    //write
    //close
    gFd = open("./CFIFO", O_RDONLY| O_NONBLOCK);
    
    
    close (gFd);
    
    
    remove("./CFIFO");
    
    
    return 0;
}