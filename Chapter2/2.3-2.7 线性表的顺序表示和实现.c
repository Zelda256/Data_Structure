#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LISTINCREMENT 10   //线性表存储空间的分配增量

typedef int Status;
typedef int ElemType;

typedef struct
{
    ElemType *elem;  //存储空间基址
    int length;  //当前长度
    int listsize;  //当前分配的存储容量（以sizeof(ElemType)为单位
}SqList;

/*******************************声明部分****************************************/

Status InitList_Sq(SqList *L);
//构造一个空的线性表L

Status ListInsert_Sq(SqList *L,int i,ElemType e);
//在顺序线性表L中第i个位置之前插入新的元素e
//i的合法位置为 1<= i<=(*L).length+1

Status ListTraverse(SqList L);
//打印线性表L中存储的元素

Status ListDelete_Sq(SqList *L,int i,ElemType *e);
//在顺序线性表L中删除第i个元素，并用e返回其值
//i的合法值为：  1<=i<=L.length

int compare(ElemType a,ElemType b);
int LocateElem_Sq(SqList L,ElemType e);
//在顺序线性表L中查找第一个与e相同的位置
//若找到，则返回在L中的位置，否则，返回0

void MergeList_Sq(SqList La,SqList Lb,SqList *Lc);
//已知顺序线性表La和Lb的元素按非递减排列
//归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列

/*******************************函数部分****************************************/

Status InitList_Sq(SqList *L)
{
    (*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!(*L).elem)
        exit(OVERFLOW);
    (*L).length = 0;
    (*L).listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList *L,int i,ElemType e)
{
    if(i<1 || i>(*L).length+1)
        return ERROR;  //i值不合法
    if((*L).length >= (*L).listsize){  //当前存储空间已满，增加分配
        ElemType *newbase;
        newbase = (ElemType *)realloc((*L).elem,((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase)
            exit(OVERFLOW);
        (*L).elem = newbase;  //新基址
        (*L).listsize += LISTINCREMENT;  //增加存储容量
    }//if
    ElemType *q,*p;
    q = &((*L).elem[i-1]); //q为插入位置
    for(p = &((*L).elem[(*L).length - 1]); p>=q; --p)
        *(p+1) = *p;  //插入位置及之后的元素右移
    *q = e;  //插入e
    ++(*L).length;  //表长增1
    return OK;
}

Status ListTraverse(SqList L)
{
    printf("L中的元素有：");
    int count;
    for(count = 0;count < L.length;count++)
        printf("%d", L.elem[count]);
    printf("\n");
    return OK;

}

Status ListDelete_Sq(SqList *L,int i,ElemType *e)
{
    if(i<1 || i>(*L).length)
        return ERROR;  //i值不合法
    ElemType *p,*q;
    p = &((*L).elem[i-1]);  //p为被删除元素的位置
    *e = *p;  //被删除元素的值赋给e
    q = (*L).elem + (*L).length +1;  //表尾元素的位置
    for(++p;p<=q;++p)
        *(p-1) = *p; //被删除元素之后的元素左移
    --(*L).length;
    return OK;
}

int compare(ElemType a,ElemType b)
{
    return a-b;
}

int LocateElem_Sq(SqList L,ElemType e)
{
    int i = 1;  //i的初值为第一个元素的位序
    ElemType *p;
    p = L.elem;   //p的初值为第一个元素的存储位置
    while(i <= L.length && compare(*p++,e) != 0)
        ++i;
    if(i<=L.length)
        return i;
    else
        return 0;
}

void MergeList_Sq(SqList La,SqList Lb,SqList *Lc)
{
    ElemType *pa,*pb,*pc,*pa_last,*pb_last;
    pa = La.elem;
    pb = Lb.elem;
    (*Lc).listsize = (*Lc).length = La.length + Lb.length;
    pc = (*Lc).elem = (ElemType *)malloc((*Lc).listsize * sizeof(ElemType));
    if(!(*Lc).elem)
        exit(OVERFLOW);
    pa_last = La.elem+La.length-1;
    pb_last = Lb.elem+Lb.length-1;
    while(pa<=pa_last && pb<=pb_last){   //归并
        if(*pa <= *pb)
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }
    while(pa<=pa_last)  //插入La剩余元素
        *pc++ = *pa++;
    while(pb<=pb_last)  //插入Lb剩余元素
        *pc++ = *pb++;

}

/*******************************主函数部分**************************************/
int main()
{
    SqList L,La,Lb,Lc;
    InitList_Sq(&L);
    InitList_Sq(&La);
    InitList_Sq(&Lb);
    InitList_Sq(&Lc);

    int count;
    for(count = 1;count<=5;count++)
        ListInsert_Sq(&L,count,count);
    ListTraverse(L);

    ElemType e;
    ListDelete_Sq(&L,2,&e);
    printf("\n被删除的元素为%d\n",e);
    ListTraverse(L);

    printf("\n元素 4 在线性表L中的位序为： %d\n",LocateElem_Sq(L,4));

    printf("\n下面为La赋值12345：\n");
    for(count = 1;count<=5;count++)
        ListInsert_Sq(&La,count,count);
    ListTraverse(La);

    printf("\n下面为Lb赋值1234567：\n");
    for(count = 1;count<=7;count++)
        ListInsert_Sq(&Lb,count,count);
    ListTraverse(Lb);

    printf("\n下面合并La和Lb到Lc\n");
    MergeList_Sq(La,Lb,&Lc);
    ListTraverse(Lc);
    return 0;
}


