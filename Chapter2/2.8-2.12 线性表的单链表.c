#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

/*******************************声明部分****************************************/

Status GetElem_L(LinkList L,int i,ElemType *e);
//L为带头结点的单链表的头指针
//当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR

void CreateList_L (LinkList *L,int n);
//逆位序输入n个元素的值，建立带头结点的单链线性表L
//（已改为自动生成）

Status ListTraverse_L(LinkList L);
//打印L中的元素

Status ListInsert_L(LinkList *L,int i,ElemType e);
//在带头结点的单链线性表L中第i个位置之前插入元素e

Status ListDelete_L(LinkList *L,int i,ElemType *e);
//在带投机诶单的单链线性表L中，删除第i个元素，并由e返回其值

void MergeList_L(LinkList *La,LinkList *Lb,LinkList *Lc);
//已知单链线性表La和Lb的元素按值非递减排列
//归并La和Lb得到新的单链线性表Lc，Lc也按值非递减排列

/*******************************函数部分****************************************/

Status GetElem_L(LinkList L,int i,ElemType *e)
{
    LinkList p;
    p = L->next;  //初始化，p指向第一个结点
    int count = 1;
    while(p && count < i){  //顺指针向后查找，直到p指向第i个元素或p为空
        p = p->next;
        ++count;
    }
    if(!p || count>i)
        return ERROR;  //第i个元素不存在
    *e = p->data;
    return OK;
}

void CreateList_L (LinkList *L,int n)
{
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;  //建立一个带头结点的单链表
    int count;
    for(count = n;count>0;count--){
        LinkList p;
        p = (LinkList)malloc(sizeof(LNode)); //生成新结点
        p->data = count;
        p->next = (*L)->next;
        (*L)->next = p; //插入到表头
    } //for
}

Status ListTraverse_L(LinkList L)
{
    LinkList p;
    p = L->next;
    printf("\nL中的元素有：");
    while(p){
        printf(" %d ",p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

Status ListInsert_L(LinkList *L,int i,ElemType e)
{
    LinkList p;
    p = *L;
    int count = 0;
    while(p && count<i-1){
        p = p->next;
        ++count;  //寻找第i-1个结点
    }
    if(!p || count>i-1)
        return ERROR;
    LinkList s;
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;  //插入L中
    return OK;
}

Status ListDelete_L(LinkList *L,int i,ElemType *e)
{
    LinkList p;
    p = *L;
    int count = 0;
    while(p->next && count<i-1){
        p = p->next;
        ++count;  //寻找第i个结点
    }
    if(!p->next || count>i-1)
        return ERROR;
    LinkList s;
    s = p->next;
    p->next = s->next;
    *e = s->data;
    free(s);   //删除并释放结点
    return OK;
}

void MergeList_L(LinkList *La,LinkList *Lb,LinkList *Lc)
{
    LinkList pa,pb,pc;
    pa = (*La)->next;
    pb = (*Lb)->next;
    *Lc = pc = *La;  //用La的头结点作为Lc的头结点
    while(pa && pb){
        if(pa->data <= pb->data){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else{
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }//while
    pc->next = pa?pa:pb;  //插入剩余段
    free(*Lb);
}

/*******************************主函数部分**************************************/

int main()
{
    LinkList L;
    CreateList_L(&L,5);
    ListTraverse_L(L);

    ElemType e;
    GetElem_L(L,2,&e);
    printf("\nL中的第 2 个元素为 %d\n",e);

    printf("\n\n下面在L的第4个元素前插入‘6’\n");
    ListInsert_L(&L,4,6);
    ListTraverse_L(L);

    ElemType e1;
    printf("\n\n下面将删除L中的第5个元素 \n");
    ListDelete_L(&L,5,&e1);
    ListTraverse_L(L);
    printf("被删除的元素为 %d\n",e1);

    printf("\n\n下面将La=123 ,Lb=1234567 合并到Lc中\n");
    LinkList La,Lb,Lc;
    CreateList_L(&La,3);
    CreateList_L(&Lb,7);
    MergeList_L(&La,&Lb,&Lc);
    printf("下面将打印Lc中的元素\n");
    ListTraverse_L(Lc);

    return 0;
}
