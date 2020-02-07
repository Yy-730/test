#ifndef __LIST_H
#define __LIST_H

//节点
struct node_st {
	void *data; //数据域
	struct node_st *next; //指针域
};

typedef struct {
	struct node_st headnode;
	int size;
}head_t;

enum{
	HEAD_INSERT,
	TAIL_INSERT
};

typedef int (*cmp_t)(const void *data,const void *key);
typedef void (*pri_t)(const void *data);
//创建头结点
int listhead_init(int size,head_t **head);

//增
int list_insert(head_t *head,const void *data,int way);

//删
int list_delete(head_t *head,const void *key,cmp_t cmp);

//查
void *list_find(const head_t *head,const void *key,cmp_t cmp);

//遍历
void *list_show(const head_t *head,pri_t pri);

//清空
void list_destroy(const head_t *head);
//--------------------------------------------------------
//遍历环
void *list_show_link(const head_t *head,pri_t pri);
//生成环
int list_insert_tail_link(head_t *head,const void *data);
//找环
struct node_st *list_find_link(const head_t *head);
#endif
