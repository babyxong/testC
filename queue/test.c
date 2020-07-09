/*************************************************************************************************************************

    功能：演示循环队列的基本操作
        1) 循环队列初始化
        2）入队操作
        3）出队操作
        4）判断是否为空队列
        5）判断队列是否已满
        6）遍历队列各元素
    注：为了避免队列空和满两个状态混淆，采用空闲一个位置的方式，即N个元素空间的循环队列最多只能存放N-1个有效元素。

**************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>   //注意使用布尔类型时，需要引入此头文件

/*******************************************************************************************************************

    定义循环队列的结构体
    注：循环队列是在数组的基础上实现的，所以需要一个指向首元素的指针，另外头和尾用int来表示相对偏移量即可。

********************************************************************************************************************/
typedef struct Queue
{
    int * qBase;
    int front;
    int rear;
}QUEUE;

void initQueue(QUEUE *pq);
void enQueue(QUEUE *pq , int value);
bool isemptyQueue(QUEUE *pq);
bool is_fullQueue(QUEUE *pq);
void deQueue(QUEUE *pq , int *value);
void traverseQueue( QUEUE *pq);

/***********************************************

    主函数测试入口

************************************************/
int main()
{
    int val;
    QUEUE queue = {NULL,0,0} ;
    initQueue(&queue);
    enQueue(&queue,4);
    enQueue(&queue,5);
    enQueue(&queue,6);
    enQueue(&queue,7);
    enQueue(&queue,72);
    enQueue(&queue,42);


    traverseQueue(&queue);
    deQueue(&queue , &val);
    deQueue(&queue , &val);

    traverseQueue(&queue);
    enQueue(&queue,55);
    enQueue(&queue,65);
    traverseQueue(&queue);


    return 0;
}
/************************************
    初始化一个空的循环队列
************************************/
void initQueue(QUEUE *pq)
{
    pq->qBase = (int *)malloc(sizeof(int)*6);
    if(pq->qBase == NULL)
    {
        printf("内存分配失败！\n");
        exit(-1);
    }
    pq->front = pq->rear = 0;

}
/************************************************************

    插入一个新元素

    注：插入前需要先判断该队列是否已满，避免覆盖有效数据。

************************************************************/

void enQueue(QUEUE *pq , int value)
{

    if(is_fullQueue(pq))
    {
        printf("循环队列已满，拒绝插入%d！\n",value);

    }else
    {
        pq->qBase[pq->rear] = value;
        pq->rear = (pq->rear + 1)%6 ;
        printf("\n %d 入队 \n" , value);

    }
}

/*************************************

    删除一个元素,并通过指针返回该数

    注:删除前要判断该队列是否为空。

*************************************/

 void deQueue(QUEUE *pq , int *value)
 {

    if(isemptyQueue(pq))
    {
        printf("循环队列已空！");
    }else
    {
        *value = pq->qBase[pq->front];
        printf("\n %d 出队 \n",*value);
        pq->front = (pq->front + 1)%6 ;

    }

 }

/************************************

    判断循环队列是否为空

************************************/
bool isemptyQueue(QUEUE *pq)
{
    if(pq->front == pq->rear)
    {
        return true;
    }else
        return false;
}

/************************************
    判断循环队列是否已满
************************************/
bool is_fullQueue(QUEUE *pq)
{
    if((pq->rear +1)%6 == pq->front)
    {
        return true;
    }else
        return false;
}

/*************************************

    遍历循环队列中的各元素
*************************************/
void traverseQueue( QUEUE *pq)
{
    if(isemptyQueue(pq))
    {
        printf("循环队列为空!\n");
        exit(0);
    }
    printf("当前循环队列 :\n");
    printf("front是%d,rear是%d :\n",pq->front,pq->rear);


    int tail = pq->front ;
    while(tail != pq->rear)
    {
        printf(" %d ",pq->qBase[tail]);
        tail = (tail + 1)%6;

    }
}