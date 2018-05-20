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

typedef SqList HeapType;
/*******************************声明部分****************************************/
Status CreateSqList(SqList *L);
//创建顺序表
Status TraverseSqList(SqList L);
//打印顺序表


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

void HeapAdjust(HeapType *H,int s,int m)
{
    RedType rc;
    int i,j;

    rc = H->r[s];
    for(j = 2*s; j <= m; j *= 2){
        if(j < m && LT(H->r[j].key,H->r[j+1].key))
            j++;
        if(!LT(rc.key,H->r[j].key))
            break;
        H->r[s] = H->r[j];
        s = j;
    }
    H->r[s] = rc;
}

void HeapSort(HeapType *H)
{
    int i;
    RedType temp;

    for(i = H->length/2; i > 0;--i)
        HeapAdjust(H,i,H->length);
    for(i = H->length; i > 1; --i){
        temp = H->r[1];
        H->r[1] = H->r[i];
        H->r[i] = temp;
        HeapAdjust(H,1,i-1);
    }
}

/*******************************主函数部分**************************************/
int main()
{
    HeapType H;

    printf("创建顺序表：\n");
    CreateSqList(&H);
    TraverseSqList(H);

    printf("堆排序：\n");
    HeapSort(&H);
    TraverseSqList(H);
    return 0;
}



