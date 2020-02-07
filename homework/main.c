#include <stdio.h>
#include "list.h"
static void pri_num(const void *data)
{
	const int *d=data;
	printf("%d\n",*d);
}

static int cmp_num(const void *data,const void *key)
{
	const int *m=data;
	const int *n=key;
	return *m-*n;
}

int main(void)
{
	int arr[]={1,2,3,4,5};
	head_t *head=NULL;
	if(listhead_init(sizeof(int),&head)!=0)
		return 1;
	for(int i=0;i<sizeof(arr)/sizeof(*arr);i++){
		list_insert(head,arr+i,TAIL_INSERT);
	}
	int s=6;
	list_insert_tail_link(head,&s);
	list_show_link(head,pri_num);
	//list_show(head,pri_num);
	struct node_st *p=list_find_link(head);
	if(p!=NULL)
	{
		printf("存在环结构,环的入口为:");
		pri_num(p->data);
	}
	return 0;
}
