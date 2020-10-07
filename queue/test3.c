
/*************************************************************************
  > File Name: linkqueue.c
  > Author: Wenfei6316
  > Mail: Wenfei6316@163.com 
  > Created Time: 2018年06月19日 星期二 08时01分25秒
 ************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
typedef enum{false, true} bool;

typedef int data_t;

typedef struct LinkNode
{
	data_t data;
	struct LinkNode *next;
}LinkNode, *LinkQueue;
 
typedef struct
{
	LinkQueue front, rear;
	int num;	
}HeadQueue;
 
HeadQueue *CreateEmptyQueue(void);
bool EmptyLinkQueue(HeadQueue *queue);
void EnQueue(HeadQueue *queue, data_t value);
void DeQueue(HeadQueue *queue, data_t *value);
void PrintQueue(HeadQueue *queue);
bool ClearLinkQueue(HeadQueue *queue);
bool DestroyLinkQueue(HeadQueue *queue);
 
int main(int argc, const char *argv[])
{
	data_t data;
	int i;
	HeadQueue *queue;
	queue = CreateEmptyQueue();
 
	EnQueue(queue, 20);
	EnQueue(queue, 30);
 
	DeQueue(queue, &data);
	printf("data is %d\n", data);
	DeQueue(queue, &data);
	printf("data is %d\n", data);
	DeQueue(queue, &data);
	printf("data is %d\n", data);
 
	for (i=0; i<20; i++)
		EnQueue(queue, i);
	PrintQueue(queue);
	for (i=0; i<25; i++)
	{
		DeQueue(queue, &data);
		printf("data is %d\n", data);
	}
 
	if (DestroyLinkQueue(queue))
		printf("DestroyLinkQueue success!\n");
	return 0;
}
 
//创建空链表队列
HeadQueue *CreateEmptyQueue(void)
{
	HeadQueue *queue;
	queue = (HeadQueue *)malloc(sizeof(HeadQueue));
	if (queue == NULL)
	{
		perror("Create empty queue failed");
		exit(EXIT_FAILURE);
	}
	queue->rear = queue->front = NULL;
	queue->num  = 0;
 
	return queue;
}
 
//判断是否为空链表队列
bool EmptyLinkQueue(HeadQueue *queue)
{
	if (queue == NULL)
	{
		printf("Empty link queue error!\n");
		exit(EXIT_FAILURE);
	}
	return queue->front == NULL ? true : false;
}
 
//增加队列元素
void EnQueue(HeadQueue *queue, data_t value)
{
	LinkQueue new;
	if (queue == NULL)
	{
		printf("EnQueue Error!\n");
		return ;
	}
	new = (LinkQueue)malloc(sizeof(LinkNode));
	if (new == NULL)
	{
		perror("Insert value failed");
		return ;
	}
	new->data = value;
	new->next = NULL;
 
	if (EmptyLinkQueue(queue))
		queue->front = queue->rear = new;
	else
	{
		queue->rear->next = new;
		queue->rear = new;
		queue->num++;
	}
 
	return ;
}
 
//删除队列元素
void DeQueue(HeadQueue *queue, data_t *value)
{
	*value = 0;
	LinkQueue remove;
	if (queue == NULL)
	{
		printf("DeQueue error!\n");
		return ;
	}
 
	if (EmptyLinkQueue(queue))
	{
		printf("queue is empty!\n");
		return ;
	}
	remove = queue->front;
	queue->front = remove->next;
	queue--;
 
	if (queue->front == NULL)
		queue->rear = NULL;
 
	*value = remove->data;
	free(remove);
 
	return ;
}
 
//遍历队列元素
void PrintQueue(HeadQueue *queue)
{
	LinkQueue node;
	printf("queue = {");
	node = queue->front;
	if (node == NULL)
	{
		printf("}\n");
		return ;
	}
	while (node != NULL)
	{
		printf("%d,", node->data);
		node = node->next;
	}
	printf("\b}\n");
 
	return ;
 
}
 
//清空队列元素
bool ClearLinkQueue(HeadQueue *queue)
{
	LinkQueue remove;
	remove = queue->front;
	while (remove != NULL)
	{
		queue->front = queue->front->next;
		free(remove);
		remove = queue->front;
	}
	queue->front = NULL;
	queue->rear = NULL;
 
	return true;
}
 
//销毁队列
bool DestroyLinkQueue(HeadQueue *queue)
{
	if (queue != NULL)
	{
		ClearLinkQueue(queue);
		free(queue);
		return true;
	}
	else
	{
		printf("DestroyLinkQueue error!\n");
		return false;
	}
}

	
