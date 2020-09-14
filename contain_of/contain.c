#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <linux/kernel.h>
typedef struct
{
    int num;
    char a;
}node;


   
#define container_of2(ptr, type, member) ({                      \
        (type *) ((char *) ptr - offsetof(type, member));})  
 
void main()
{
    node* p = (node*)malloc(sizeof(node));
    p->num = 1;
    p->a = 'a';
    printf("offsetof:%lu\n",offsetof(node,num));
    printf("addr:%lu\n",p);
    printf("containerof:%lu\n",container_of(&(p->a), node, a));
}