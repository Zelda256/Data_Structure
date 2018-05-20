#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAXSIZE 125  //假设非零元个数的最大值为125  //原书为12500

typedef int Status;
typedef int ElemType;

typedef struct
{
    int i,j;  //该非零元的行下标和列下标
    ElemType e;
}Triple;
typedef struct
{
    Triple data[MAXSIZE + 1];  //非零元三元组表，data[0]未用
    int mu,nu,tu;   //矩阵的行数，列数和非零元个数
}TSMatrix;   //稀疏矩阵的一种压缩存储方式


/*******************************声明部分****************************************/
Status CreateTSMatrix (TSMatrix *M);
//创建三元组顺序表存储结构的稀疏矩阵M
Status PrintTSMatrix(TSMatrix M);
//打印稀疏矩阵M
Status TransposeSMatrix(TSMatrix M,TSMatrix *T);
//采用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵T
Status FastTransposeSMatrix(TSMatrix M,TSMatrix *T);
//采用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵T
/*******************************函数部分****************************************/
Status CreateTSMatrix (TSMatrix *M)
{
   /* printf("请输入矩阵的行数：");
    scanf("%d",& M->mu);
    printf("请输入矩阵的列数：");
    scanf("%d",& M->nu);
    printf("请输入矩阵的非零元个数：");
    scanf("%d",& M->tu);

    int i,j,k;
    for(k = 1;k<= M->tu;k++){
        printf("请输入第 %d 个非零元的信息\n",k);
        printf("请输入行号：\n");
        scanf("%d",&M->data[k].i);
        printf("请输入列号\n");
        scanf("%d",&M->data[k].j);
        printf("请输入值：\n");
        scanf("%d",&M->data[k].e);
    }*/
    M->mu = 6;
    M->nu = 7;
    M->tu = 8;
    M->data[1].i = 1;
    M->data[1].j = 2;
    M->data[1].e = 12;

    M->data[2].i = 1;
    M->data[2].j = 3;
    M->data[2].e = 9;

    M->data[3].i = 3;
    M->data[3].j = 1;
    M->data[3].e = -3;

    M->data[4].i = 3;
    M->data[4].j = 6;
    M->data[4].e = 14;

    M->data[5].i = 4;
    M->data[5].j = 3;
    M->data[5].e = 24;

    M->data[6].i = 5;
    M->data[6].j = 2;
    M->data[6].e = 18;

    M->data[7].i = 6;
    M->data[7].j = 1;
    M->data[7].e = 15;

    M->data[8].i = 6;
    M->data[8].j = 4;
    M->data[8].e = -7;

}

Status PrintTSMatrix(TSMatrix M)
{
    int k;

    printf("i j v\n");
    for(k = 1;k<= M.tu;k++)
        printf("%d %d %d\n",M.data[k].i,M.data[k].j,M.data[k].e);
}

Status TransposeSMatrix(TSMatrix M,TSMatrix *T)
{
    int p,q,col;
    T->mu = M.nu;
    T->nu = M.mu;
    T->tu = M.tu;
    if(T->tu){
        q = 1;
        for(col = 1;col<=M.nu;col++)
            for(p = 1;p<=M.tu;p++){
                if(M.data[p].j == col){
                    T->data[q].i = M.data[p].j;
                    T->data[q].j = M.data[p].i;
                    T->data[q].e = M.data[p].e;
                    q++;
                }//if
            }//for
    }//if
    return OK;
}

Status FastTransposeSMatrix(TSMatrix M,TSMatrix *T)
{
    int col,t,p,q,num[M.nu],cpot[M.nu];
    T->mu = M.nu;
    T->nu = M.mu;
    T->tu = M.tu;
    if(T->tu){
        for(col = 1;col <= M.nu;col++)
            num[col] = 0;
        for(t = 1;t<=M.tu;t++)
            ++num[M.data[t].j];  //求M中每一列含非零元个数
        cpot[1] = 1;
        //求第col列中第一个非零元在b.data中的序号
        for(col = 2;col<=M.nu;col++)
            cpot[col] = cpot[col-1]+num[col-1];
        for(p = 1;p<=M.tu;p++){
            col = M.data[p].j;
            q = cpot[col];
            T->data[q].i = M.data[p].j;
            T->data[q].j = M.data[p].i;
            T->data[q].e = M.data[p].e;
            ++cpot[col];
        }//for
    }//if
    return OK;
}
/*******************************主函数部分**************************************/
int main()
{
    TSMatrix M,T,Q;
    CreateTSMatrix(&M);
    printf("M矩阵的三元组表示为：\n");
    PrintTSMatrix(M);
    TransposeSMatrix(M,&T);
    printf("\nT矩阵的三元组表示为：\n");
    PrintTSMatrix(T);
    FastTransposeSMatrix(M,&Q);
    printf("\nQ经快速转置后：\n");
    PrintTSMatrix(Q);
    return 0;
}



