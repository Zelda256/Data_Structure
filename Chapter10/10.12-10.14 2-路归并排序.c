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
}RcdType;
typedef struct
{
    RcdType r[MAXSIZE+1];  //0号单元置空或用作哨兵
    int length;
}SqList;

/*******************************声明部分************************************/
Status CreateSqList(SqList *L);
//创建顺序表
Status TraverseSqList(SqList L);
//打印顺序表


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

    L->length = 7;

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

void Merge(RcdType SR[],RcdType TR[],int i,int m,int n)
{
    int j,k;

    for(j = m+1, k = i; i<=m && j <= n; ++k){
        if(LQ(SR[i].key,SR[j].key))
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
    }
    if(i <= m){
        int ct1,ct2;
        for(ct1 = k,ct2 = i;ct1<=n,ct2<=m;++ct1,++ct2)
            TR[ct1] = SR[ct2];
    }
    if(j <= n){
        int ct1,ct2;
        for(ct1 = k,ct2 = j;ct1<=n,ct2<=n;++ct1,++ct2)
            TR[ct1] = SR[ct2];
    }
}

void MSort(RcdType SR[],RcdType TR1[],int s,int t)
{
    RcdType TR2 [MAXSIZE+1];
    if(s==t)
        TR1[s] = SR[s];
    else{
        int m = (s+t)/2;
        MSort(SR,TR2,s,m);
        MSort(SR,TR2,m+1,t);
        Merge(TR2,TR1,s,m,t);
    }
}
void MergeSort(SqList *L)
{
    MSort(L->r,L->r,1,L->length);
}
/*******************************主函数部分**********************************/
int main()
{
    SqList L;

    printf("创建顺序表：\n");
    CreateSqList(&L);
    TraverseSqList(L);

    printf("2-路归并排序：\n");
    MergeSort(&L);
    TraverseSqList(L);
    return 0;
}



