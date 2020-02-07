#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernellist.h"
#define NAMESIZE 32
#define PHONESIZE 32
struct data_st {
	char name[NAMESIZE];
	int age;
	char phone[PHONESIZE];
	struct list_head node;
};
//增
int list_insert(struct data_st *head,char *name,int age,char *phone)
{
	struct data_st *new=malloc(sizeof(struct data_st));
	if(NULL==new)
		return -1;
	strcpy(new->name,name);
	new->age=age;
	strcpy(new->phone,phone);
	list_add_tail(&new->node,&head->node);
	return 0;
}
//查
struct data_st *list_find(struct data_st *head,char *name)
{
	struct data_st *data=head;
	struct list_head *p=&head->node;
	list_for_each(p,&head->node){
		data=list_entry(p, struct data_st, node);
		if(strcmp(data->name,name)==0)
			//return data->name;
			return data;
		else 
			return NULL;
	}
}
//删
int list_delete(struct data_st *head,char *name)
{
	struct data_st *f=list_find(head,name);
	if(strcmp(f->name,name)==0)
	{
		list_del(&f->node);
		printf("%s is delete\n",name);
		f=NULL;
		return 0;
	}
	else
		printf("没有这个人\n");
	return 0;
}
//改
int list_updata(struct data_st *head,char *name,char *newname,int age,char *phone)
{
	struct data_st *f=list_find(head,name);
	struct data_st *new=malloc(sizeof(struct data_st));
	if(NULL==new)
		return -1;
	strcpy(new->name,newname);
	new->age=age;
	strcpy(new->phone,phone);
	list_replace(&f->node,&new->node);
	return 0;
}
//查
int list_find_node(struct data_st *head,char *name)
{
	struct data_st *f=list_find(head,name);
	if(strcmp(f->name,name)==0)
	{
		printf("you find %s\n",name);
		printf("age:%d phone:%s\n",f->age,f->phone);
		f=NULL;
		return 0;
	}
	else{
		printf("未找到\n");
		return 1;
	}
	return 0;
	
}

void show_list(struct data_st *head)
{
	struct data_st *data;
	struct list_head *pos=&data->node;
	data=head;int sum=0;
	list_for_each(pos,&head->node) {
		data = list_entry(pos, struct data_st, node);
		printf("%s %d %s\n", data->name,data->age,data->phone);
		sum++;
	}
	printf("现在表里共有%d人\n",sum);
}

int main(void)
{
	struct data_st *head;
	struct list_head *pos;
	head=malloc(sizeof(struct data_st));
	if(head==NULL)
		return -1;
    INIT_LIST_HEAD(&(head->node));
	char name[NAMESIZE];
	char newname[NAMESIZE];
	int age;
	char phone[PHONESIZE];
	int num;
	while(1)
	{
		puts("######学生管理系统######");
		puts("------1.增加学生信息----");
		puts("------2.删除学生信息----");
		puts("------3.修改学生信息----");
		puts("------4.查询学生信息----");
		puts("------5.显示学生信息----");
		puts("------6.退出管理系统----");
		printf("请输入对应的num:");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
				printf("姓名:");
				scanf("%s",name);
				printf("年龄:");
				scanf("%d",&age);
				printf("电话:");
				scanf("%s",phone);
				list_insert(head,name,age,phone);
				break;
			case 2:
				printf("删谁啊:");
				scanf("%s",name);
				list_delete(head,name);
				break;
			case 3:
				printf("要该谁?");
				scanf("%s",name);
				printf("改姓名:");
				scanf("%s",newname);
				printf("改年龄:");
				scanf("%d",&age);
				printf("改电话:");
				scanf("%s",phone);
				list_updata(head,name,newname,age,phone);
				break;
			case 4:
				printf("找谁呀:");
				scanf("%s",name);
				list_find_node(head,name);
				break;
			case 5:
				show_list(head);
				break;
			case 6:
				printf("bye bye ~\n");
				exit(0);
			default:
				printf("能力有限,请重新选择:\n");
				continue;
				break;
		}
	}



	return 0;
}
