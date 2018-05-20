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
/*******************************声明部分************************************/
Status CreateSqList(SqList *L);
//创建顺序表
Status TraverseSqList(SqList L);
//打印顺序表
int Partition_1(SqList *L,int low,int high);
//交换顺序表L中子表L.r[low,high]的记录，使枢轴记录到位，并返回其位置，
//此时它之前(后)的记录均不大（小）于它
int Partition_2(SqList *L,int low,int high);
//交换顺序表L中子表L.r[low,high]的记录，使枢轴记录到位，并返回其位置，
//此时它之前(后)的记录均不大（小）于它
void QSort_1(SqList *L,int low,int high);
//对顺序表L中的子序列L.r[low...high]作快速排序
void QSort_2(SqList *L,int low,int high);
//对顺序表L中的子序列L.r[low...high]作快速排序
/*******************************函数部分************************************/
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

int Partition_1(SqList *L,int low,int high)
{
    RedType temp;
    int pivotkey = L->r[low].key;
    while(low < high){
        while(low < high && L->r[high].key >= pivotkey)
            --high;
        temp = L->r[low];
        L->r[low] = L->r[high];
        L->r[high] = temp;
        while(low < high && L->r[low].key <= pivotkey)
            ++low;
        temp = L->r[low];
        L->r[low] = L->r[high];
        L->r[high] = temp;
    }
    return low;
}

int Partition_2(SqList *L,int low,int high)
{
    int pivotkey;
    L->r[0] = L->r[low];
    pivotkey = L->r[low].key;
    while(low < high){
        while(low < high && L->r[high].key >= pivotkey)
            --high;
        L->r[low] = L->r[high];
        while(low < high && L->r[low].key <= pivotkey)
            ++low;
        L->r[high] = L->r[low];
    }
    L->r[low] = L->r[0];
    return low;

}

void QSort_1(SqList *L,int low,int high)
{
    int pivoloc;
    if(low < high){
        pivoloc = Partition_1(L,low,high);
        QSort_1(L,low,pivoloc-1);
        QSort_1(L,pivoloc+1,high);
    }
}

void QSort_2(SqList *L,int low,int high)
{
    int pivoloc;
    int ct;
    if(low < high){
        pivoloc = Partition_1(L,low,high);
        for(ct = 1;ct <=L->length;++ct)
            printf("%d ",L->r[ct]);
        printf("\n\n");
        QSort_2(L,low,pivoloc-1);
        QSort_2(L,pivoloc+1,high);
        /*Output*/
    }

}

void QuickSort(SqList *L)
{
    QSort_1(L,1,L->length);
}

/*******************************主函数部分**********************************/
int main()
{
    SqList L1,L2;

    printf("创建一个顺序表：\n");
    CreateSqList(&L1);
    TraverseSqList(L1);

    printf("\n使用算法10.6(a)快速排序：\n");
    QSort_1(&L1,1,L1.length);
    TraverseSqList(L1);

    CreateSqList(&L2);
    printf("\n使用算法10.6(b)快速排序：\n");
    QSort_2(&L2,1,L2.length);
    printf("最终结果：\n");
    TraverseSqList(L2);
    return 0;
}



