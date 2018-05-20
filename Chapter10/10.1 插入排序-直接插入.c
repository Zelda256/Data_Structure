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
void InsertSort(SqList *L);
//对顺序表L作直接插入排序
Status CreateSqList(SqList *L);
//创建顺序表
Status TraverseSqList(SqList L);
//打印顺序表
/*******************************函数部分****************************************/
void InsertSort(SqList *L)
{
    int i,j;

    for(i = 2;i <= L->length;++i){
        if(LT(L->r[i].key , L->r[i-1].key)){
            L->r[0] = L->r[i];  //复制为哨兵
            L->r[i] = L->r[i-1];
            for(j = i-2; LT(L->r[0].key , L->r[j].key); --j)
                L->r[j+1] = L->r[j];  //后移
            L->r[j+1] = L->r[0];  //插入
        }//if
    }//for
}

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

/*******************************主函数部分**************************************/
int main()
{
    SqList L;
    printf("创建一个顺序表：\n");
    CreateSqList(&L);
    TraverseSqList(L);

    printf("\n直接插入排序后：\n");
    InsertSort(&L);
    TraverseSqList(L);
}



