#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef ElemType *Triplet;  //由InitTriplet分配3个元素空间
/*******************************声明部分****************************************/

Status InitTriplet (Triplet *T,ElemType v1,ElemType v2,ElemType v3);
Status DestroyTriplet(Triplet *T);
Status Get(Triplet T,int i,ElemType *e);
Status Put(Triplet *T,int i,ElemType e);
Status IsAscendig(Triplet T);
Status IsDescending(Triplet T);
Status Max(Triplet T,ElemType *e);
Status Min(Triplet T,ElemType *e);

/*******************************函数部分****************************************/

Status InitTriplet (Triplet *T,ElemType v1,ElemType v2,ElemType v3)
{
    (*T) = (ElemType *)malloc(3*sizeof(ElemType));
    if(!(*T))
        exit(OVERFLOW);
    (*T)[0] = v1;
    (*T)[1] = v2;
    (*T)[2] = v3;
    return OK;
}
Status DestroyTriplet(Triplet *T)
{
    free(*T);
    (*T) = NULL;
    return OK;
}
Status Get(Triplet T,int i,ElemType *e)
{
    if(i<1 || i> 3)
        return ERROR;
    *e = T[i-1];
    return OK;
}
Status Put(Triplet *T,int i,ElemType e)
{
    if(i<1 || i> 3)
        return ERROR;
    (*T)[i-1] = e;
    return OK;
}
Status IsAscendig(Triplet T)
{
    return(T[0] <= T[1]) && (T[1] <= T[2]);
}
Status IsDescending(Triplet T)
{
    return(T[0] >= T[1]) && (T[1] >= T[2]);
}
Status Max(Triplet T,ElemType *e)
{
    *e = (T[0] >= T[1]) ? ((T[0] >= T[2]) ? T[0]:T[2]) : ((T[1] >= T[2]) ? T[1] : T[2]);
    return OK;
}
Status Min(Triplet T,ElemType *e)
{
    *e = (T[0] <= T[1]) ? ((T[0] <= T[2]) ? T[0]:T[2]) : ((T[1] <= T[2]) ? T[1] : T[2]);
    return OK;
}

/*******************************主函数部分**************************************/

int main()
{
    Triplet T;
    ElemType e,e1 = 9,v1 = 5,v2 = 6,v3 = 7;

    InitTriplet(&T,v1,v2,v3);

    Get(T,2,&e);
    printf("\nGet()取出T中的第二个元素为：%d\n",e);

    printf("\n现将第二个元素置为：9\n");
    Put(&T,2,e1);
    Get(T,2,&e);
    printf("Get()取出T中的第二个元素为：%d\n",e);

    Max(T,&e);
    printf("\n三元组T中最大的元素为：%d\n",e);

    Min(T,&e);
    printf("\n三元组T中最小的元素为：%d\n",e);

    DestroyTriplet(&T);
    return 0;
}
