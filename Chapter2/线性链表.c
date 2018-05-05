#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

void CreatList_L(LinkList *L, int n);
void CreatList2_L(LinkList *L, int n);
Status GetElem_L(LinkList L, int i, ElemType *e);
Status ListInsert_L(LinkList *L,int i,ElemType e);
Status ListDelete_L(LinkList *L, int i, ElemType *e);
void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc);

void CreatList_L(LinkList *L, int n){
	//逆位序输入n个元素的值，建立带表头结点的单链线性表L；
	LNode *p;
	int i;
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;//先建立一个带头结点的单链表
	printf("请输入链表的各个元素值：") ;
	for(i = n; i > 0; --i){
		p = (LinkList)malloc(sizeof(LNode));//生成新结点
		scanf("%d",&(p->data));//输入元素值
		p->next = (*L)->next; (*L)->next = p; //插入到表头
	}

}//CreateList_L

void CreatList2_L(LinkList *L, int n){
	LNode *p,*q;
	int i;
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
	q= *L;
	printf("请输入链表的各个元素值：");
	for(i = 0; i < n; i++){
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d",&(p->data));
		q->next = p;
		q = q->next;
	}
}//CreateList2_L

Status GetElem_L(LinkList L, int i, ElemType *e){
	//L为带头结点的单链表的头指针
	//当第i个元素存在时，其值赋给e并返回OK,否则返回ERROR
	LNode *p;
	int j;
	p = L->next; j = 1;//初始化，p指向第一个结点，j为计数器
	while(p && j < i){//顺指针向后查找，直到p指向第i个元素或p为空
		p = p->next;++j;
	}
	if(!p || j > i)return ERROR;//第i个元素不存在
	*e = p->data;//取第i个元素
	return OK;
}//GetElem_L

Status ListInsert_L(LinkList *L,int i,ElemType e){
	//在带头结点的单链线性表L中第i个位置之前插入元素e
	 LNode *p,*s;
	int j;
	p = *L; j = 0;
	while(p && j < i-1){
		p = p->next; ++j;
	}//寻找第i-1个结点
	if(!p || j > i)return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete_L(LinkList *L, int i, ElemType *e){
	//在带头结点的单链线性表l中，删除第i个元素，并由e返回其值
	LNode *p,*q;
	int j;
	p = *L; j = 0;
	while(p->next && j < i-1){
		//寻找第i个结点，并令p指向其前驱
		p = p->next; ++j;
	}
	if(!(p->next) || j > i-1)return ERROR;//删除位置不合理
	q = p->next; p->next = q->next;
	*e = q->data; free(q);
	return OK;
}//ListDelete_L



void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc){
	//已知单链线性表La和Lb的元素按值非递减排列
	//归并La和Lb得到新的单链线性表Lc,Lc的元素也按值非递减排列
	LNode *pa,*pb,*pc;
	pa = (*La)->next; pb = (*Lb)->next;
	(*Lc) = pc =pa;
	while(pa && pb){
		if(pa->data <= pb->data){
			pc->next = pa; pc = pa; pa = pa->next;
		}
		else{
			pc->next = pb; pc = pb; pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free((*Lb));
}//MergeList_L

main()
{
	LinkList La,Lb,p,q;
	int n=5,i;

	CreatList_L(&La, n);
	printf("逆位序建立的线性链表为：");
	p = La->next;
	while(p){
        printf("%d->",p->data);
        p = p->next;
	}

}
















