#define _GNU_SOURCE 
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>


void closeFun(void *arg)
{
    int n = *(int*)arg;
    
    printf ("======push=1=====cancel:%d....\n", n);
}

void closeFun(void *arg)
{
    int n = *(int*)arg;
    
    printf ("=====push ==2=====cancel:%d....\n", n);
}


void *fun1(void *arg)
{
	printf("Pthread:1 come!\n");
    
    int fd =1;
    pthread_cleanup_push(closeFun, &fd);
    pthread_cleanup_push(closeFun1, &fd);
    
	while(1){
        printf("Phtread1 running============");
		sleep(1);
	}
    
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    
}

void *fun2(void *arg)
{
    int fd2 =100;
     pthread_cleanup_push(closeFun, &fd2);
    
	printf("Pthread:2 come!\n");
    sleep(3);
	pthread_cancel((pthread_t )(long)arg);
	pthread_exit(NULL);
    
        pthread_cleanup_pop(0);
}

int main()
{
	int ret,i,flag = 0;
	void *Tmp = NULL;
	pthread_t tid[2];
	ret = pthread_create(&tid[0],NULL,fun1,NULL);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	sleep(1);
	ret = pthread_create(&tid[1],NULL,fun2,(void *)tid[0]);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	while(1){
		for(i = 0;i <2;i++){
			if(pthread_tryjoin_np(tid[i],NULL) == 0){
				printf("Pthread : %d exit !\n",i+1);
				flag++;	
			}
		}
        while (1) {
            printf("sleep !\n");\
            sleep(1);
        }
		if(flag >= 2) break;
	}
	return 0;
}
