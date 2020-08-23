/*******************************
client.c
********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <assert.h>



typedef struct node* list_head;

struct node {
	unsigned char item;
	list_head next;
};

static list_head gHeadList = NULL;


list_head make_node(unsigned char item)
{
	list_head p = malloc(sizeof *p);
	p->item = item;
	p->next = NULL;
	return p;
}

void free_node(list_head p)
{
	free(p);
}

list_head search(unsigned char key)
{
	list_head p;
	for (p = gHeadList; p; p = p->next)
	{
		if (p->item == key)
		return p;
	}
	
	return NULL;
}

void insert(list_head p)
{
	p->next = gHeadList;
	gHeadList = p;
}

void delete(list_head p)
{
	list_head pre;
	
	if (p == gHeadList) 
	{		
		gHeadList = p->next;
		return;
	}
	
	for (pre = gHeadList; pre; pre = pre->next)
	{
		if (pre->next == p) 
		{
			pre->next = p->next;
			return;
		}
	}
}

void traverse(void (*visit)(list_head))
{
	list_head p;
	for (p = gHeadList; p; p = p->next)
	{
		visit(p);
	}
}
void destroy(void)
{
	list_head q, p = gHeadList;
	gHeadList = NULL;
	while (p) 
	{
		q = p;
		p = p->next;
		free_node(q);
	}
}
void push(list_head p)
{
	insert(p);
}

list_head pop(void)
{
	if (gHeadList == NULL)
	{
		return NULL;
	}
	else 
	{
		list_head p = gHeadList;
		gHeadList = gHeadList->next;
		return p;
	}
}

void print_item(list_head p)
{
	printf("%d\n", p->item);
}

int main(void)
{
	list_head p = make_node(10);
	insert(p);
	p = make_node(5);
	
	insert(p);	
	p = make_node(90);
	insert(p);
	p = search(5);
	delete(p);
	free_node(p);
	traverse(print_item);
	destroy();
	p = make_node(100);
	push(p);
	p = make_node(200);
	push(p);
	p = make_node(250);
	push(p);
	while (p = pop()) {
	print_item(p);
	free_node(p);
	}
return 0;
}