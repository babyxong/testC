/* main.c   */


#include <stdio.h>
#include <stdlib.h>

//#include "test.h"


struct person 
{
    int age;
    struct list_head list;
};


void queue_creat(struct list_head *list)
{
    INIT_LIST_HEAD(list);
}

void in_queue(struct list_head *new, struct list_head *head)
{
    list_add_tail(new,head);
}

void out_queue(struct list_head *head)
{
    struct list_head *list = head->next; /* 保存链表的最后节点 */
    
    list_del(head->next);/* 头删法 */
    
    INIT_LIST_HEAD(list); /* 重新初始化删除的最后节点，使其指向自身 */

}

int get_queue_size(struct list_head *head)
{ 
    struct list_head *pos;
    int size = 0;
    
    if (head == NULL) {
        return -1;
    }
    
    list_for_each(pos,head) {
        size++;
    }

    return size;

}

bool is_empt_queue(struct list_head *head)
{
    return list_empty(head);
}

int main(int argc,char **argv)
{
    int i;
    int num =5;
    struct person *p;
    struct person head;
    struct person *pos,*n;
    
    queue_creat(&head.list);
    
    p = (struct person *)malloc(sizeof(struct person )*num);
    
    for (i = 0;i < num;i++) {
        p->age = i*10;
        in_queue(&p->list,&head.list);
        p++;
    }
    printf("original==========>\n");
    list_for_each_entry_safe(pos,n,&head.list,list) {
        printf("age = %d\n",pos->age);
    }
    printf("size = %d\n",get_queue_size(&head.list));
    struct person test;
    test.age = 100;
    printf("out_queue %d\n",get_queue_head(pos,&head.list,list)->age);
    out_queue(&head.list);
    printf("out_queue %d\n",get_queue_head(pos,&head.list,list)->age);
    out_queue(&head.list);
    printf("in_queue %d\n",test.age);
    in_queue(&test.list,&head.list);

    printf("current==========>\n");
    list_for_each_entry_safe(pos,n,&head.list,list) {
        printf("age = %d\n",pos->age);
    }
    printf("size = %d\n",get_queue_size(&head.list));
    printf("all member out_queue\n");
    list_for_each_entry_safe(pos,n,&head.list,list) {
        out_queue(&head.list);
    }
    printf("size = %d\n",get_queue_size(&head.list));
    if (is_empt_queue(&head.list)) {
        printf("is_empt_queue\n");
    }
    
    return 0;
}