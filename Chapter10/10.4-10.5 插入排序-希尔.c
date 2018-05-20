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
typedef int KeyType;
#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) <  (b))
#define LQ(a,b) ((a) <= (b))

#define MAXSIZE 20
typedef struct
{
    KeyType key;
}RedType;
typedef struct
{
    RedType r[MAXSIZE+1];  //0号单元置空或用作哨兵
    int length;
}SqList;



/*******************************声明部分****************************************/
void ShellInsert(SqList *L,int dk);
//对顺序表L作一趟希尔插入排序
void ShelSort(SqList *L,int dlta[], int t);
//按增量序列dlta[0...t-1]对顺序表L作希尔排序
Status CreateSqList(SqList *L);
Status TraverseSqList(SqList L);
/*******************************函数部分****************************************/
void ShellInsert(SqList *L,int dk)
{
    int i,j;
    for(i = dk+1;i <= L->length;i++)
    if(LT(L->r[i].key , L->r[i-dk].key)){
        L->r[0] = L->r[i];
        for(j = i-dk; j > 0 && LT(L->r[0].key , L->r[j].key); j-=dk)
            L->r[j+dk] = L->r[j];
        L->r[j+dk] = L->r[0];
    }
}

void ShelSort(SqList *L,int dlta[], int t)
{
    int k;
    for(k = 0;k < t;k++)
        ShellInsert(L,dlta[k]);
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
    int dlta[3] = {5,3,1};
    int t = 3;

    printf("创建一个顺序表：\n");
    CreateSqList(&L);
    TraverseSqList(L);

    printf("\n希尔排序：\n");
    ShelSort(&L,dlta,3);
    TraverseSqList(L);

    return 0;
}


