#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) <  (b))
#define LQ(a,b) ((a) <= (b))

typedef int Status;
typedef int ElemType;

#define MAXSIZE 20
typedef int KeyType;
typedef char InfoType;
typedef struct
{
    KeyType key;
    InfoType otherinfo;
}RedType;
typedef struct
{
    RedType r[MAXSIZE+1];  //0号单元置空或用作哨兵
    int length;
}SqList;
/*******************************声明部分****************************************/
Status CreateSqList(SqList *L);
//创建顺序表
Status TraverseSqList(SqList L);
//打印顺序表
void SelectSort(SqList *L);
//简单选择排序
int SelectMinKey(SqList L,int i);
//在L.[i...L.length]中选择key最小的记录

/*******************************函数部分****************************************/
Status CreateSqList(SqList *L)
{
 /*   int i;
    printf("请输入长度：");
    scanf("%d",&L->length);
    for(i = 1;i <= L->length;i++){
        printf("请输入关键值：");
        scanf("%d",&L->r[i].key);
    }*/
    L->r[1].key = 49;
    L->r[2].key = 38;
    L->r[3].key = 65;
    L->r[4].key = 97;
    L->r[5].key = 76;
    L->r[6].key = 13;
    L->r[7].key = 27;
    L->r[8].key = 49;

    L->length = 8;

    return OK;
}

Status TraverseSqList(SqList L)
{
    int i;
    for(i = 1;i<=L.length;i++)
        printf("%d  ",L.r[i].key);

    printf("\n");
    return OK;
}

void SelectSort(SqList *L)
{
    int i,j;
    RedType temp;

    for(i = 1;i < L->length;++i){
        j = SelectMinKey(*L,i);
        if(i != j){
            temp = L->r[i];
            L->r[i] = L->r[j];
            L->r[j] = temp;
        }//if
    }//for
}

int SelectMinKey(SqList L,int i)
{
    int min,ct;
    min = 1;
    L.r[0] = L.r[i];

    for(ct = i; ct <= L.length; ct++){
        if(L.r[ct].key < L.r[0].key){
            min = ct;
            L.r[0] = L.r[ct];
        }
    }
    return min;
}
/*******************************主函数部分**************************************/

int main()
{
    SqList L;

    printf("创建一个顺序表：\n");
    CreateSqList(&L);
    TraverseSqList(L);

    printf("\n简单选择排序：\n");
    SelectSort(&L);
    TraverseSqList(L);
    return 0;
}


