#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

//创建头结点
int listhead_init(int size,head_t **head)
{
	head_t *h;
	h=malloc(sizeof(head_t));
	if(NULL==h)
		return -1;
	h->size=size;
	h->headnode.data=NULL;
	h->headnode.next=NULL;

	*head=h;
	return 0;
}

//增
int list_insert(head_t *head,const void *data,int way)
{
	struct node_st *new;
	struct node_st *p;
	if(!(way==HEAD_INSERT || way==TAIL_INSERT))
		return -1;
	new = malloc(sizeof(*new));
	if(NULL==new)
		return -1;
	new->data=calloc(1,head->size);
	memcpy(new->data,data,head->size);
	if(way==HEAD_INSERT)
	{
		new->next=head->headnode.next;
		head->headnode.next=new;
	}else{
		new->next=NULL;
		if(head->headnode.next==NULL)
			head->headnode.next=new;
		else{
			for(p=head->headnode.next;p->next!=NULL;
					p=p->next);
			p->next=new;
		}
	}
	return 0;
}

//找到删除的前一个节点
static struct node_st *find_pre_node(head_t *head,const void *key,cmp_t cmp)
{
	struct node_st *pre,*cur;
	pre = &head->headnode; //前节点数据域
	cur = pre->next;       //当前节点数据域
	while(cur !=NULL)
	{
		if(cmp(cur->data,key)==0)
		{return pre;}
		pre=cur;
		cur=cur->next;
	}
	return NULL;
}

//删
int list_delete(head_t *head,const void *key,cmp_t cmp)
{
	struct node_st *pre,*del;
	pre = find_pre_node(head,key,cmp);
	if(NULL==pre)
		return -1;
	del=pre->next;
	pre->next=del->next;
	del->next=NULL;
	free(del->data);
	free(del);
	return 0;
}

//查
void *list_find(const head_t *head,const void *key,cmp_t cmp){
	struct node_st *f;
	for(f=head->headnode.next;f!=NULL;f=f->next)
	{
		if(cmp(f->data,key)==0)
			return f->data;
	}
	return NULL;
}

//遍历
void *list_show(const head_t *head,pri_t pri)
{
	struct node_st *p;
	for(p=head->headnode.next;p!=NULL;p=p->next)
		pri(p->data);
}

//清空
void list_destroy(const head_t *head)
{
	struct node_st *f;
	for(f=head->headnode.next;f!=NULL;f=f->next)
	{
		f->next=NULL;
		//free(f->data);
		free(f);
		if(f->next==NULL)
			break;
	}

}

//生成环
int list_insert_tail_link(head_t *head,const void *data)
{
	struct node_st *new;
	struct node_st *p;
	new = malloc(sizeof(*new));
	if(NULL==new)
		return -1;
	new->data=calloc(1,head->size);
	memcpy(new->data,data,head->size);
	//new->next=NULL;
	if(head->headnode.next==NULL)
		head->headnode.next=new;
	else{
		for(p=head->headnode.next;p->next!=NULL;
				p=p->next);
		p->next=new;
		new->next=p;
	}
	return 0;
}
//遍历环
void *list_show_link(const head_t *head,pri_t pri)
{
	struct node_st *p;
	struct node_st *tmp;
	int count=0;
	tmp=list_find_link(head);
	for(p=head->headnode.next;p!=NULL;p=p->next)
	{
		pri(p->data);
		if(strcmp(p->data,tmp->data)==0)
		{
			count++;
		}
		if(count>=2)
			break;
	}	
}

//判断环和入口
struct node_st *list_find_link(const head_t *head)
{
	struct node_st *p1=head->headnode.next;
	struct node_st *p2=head->headnode.next;
	while(1)
	{
		p1=p1->next;
		if(NULL==p1->next)
			break;
		p2=p2->next->next;
		if(NULL==p2->next)
			break;
		if(p1==p2)
			break;
	}
	if(NULL==p2)
	{
		printf("不存在环结构");
		return NULL;
	}
	else{
		struct node_st *s1=head->headnode.next;
		struct node_st *s2=p1;
		while(s1!=s2)
		{
			s1=s1->next;
			s2=s2->next;
		}
		return s1;
	}
}
