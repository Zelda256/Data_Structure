#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdarg.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAXSIZE 125  //假设非零元个数的最大值为125  //原书为12500
#define MAXRC 20

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
    int rpos[MAXRC + 1];   //rpos[row]表示矩阵的第row行中第一个非零元在N.data中的序号
    int mu,nu,tu;   //矩阵的行数，列数和非零元个数
}RLSMatrix;   //稀疏矩阵的一种压缩存储方式

/*******************************声明部分****************************************/
Status CreateTSMatrix (RLSMatrix *M);
//创建三元组顺序表存储结构的稀疏矩阵M
Status CreateTSMatrix_AUTO(RLSMatrix *M);
//创建三元组顺序表存储结构的稀疏矩阵M
Status PrintTSMatrix(RLSMatrix M);
//打印稀疏矩阵M
Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q);
//求矩阵乘积Q = M*N，采用行逻辑链接存储表示
/*******************************函数部分****************************************/
Status CreateTSMatrix (RLSMatrix *M)
{
 /*   printf("请输入矩阵的行数：");
    scanf("%d",& M->mu);
    printf("请输入矩阵的列数：");
    scanf("%d",& M->nu);
    printf("请输入矩阵的非零元个数：");
    scanf("%d",& M->tu);

    int i,j,k,row_num,ct = 0;
    for(k = 1;k<= M->tu;k++){
        printf("请输入第 %d 个非零元的信息\n",k);
        printf("请输入行号：\n");
        scanf("%d",&M->data[k].i);
        printf("请输入列号\n");
        scanf("%d",&M->data[k].j);
        printf("请输入值：\n");
        scanf("%d",&M->data[k].e);
        if(k == 1){
            row_num = M->data[k].i;
            M->rpos[ct] = k;
            ct++;
        }

        if(row_num != M->data[k].i){  //矩阵第i行的首个非零元
            row_num = M->data[k].i;
            M->rpos[ct] = k;
            ct++;
        }
    } */

    M->mu = 3;
    M->nu = 4;
    M->tu = 4;
    M->data[1].i = 1;
    M->data[1].j = 1;
    M->data[1].e = 3;

    M->data[2].i = 1;
    M->data[2].j = 4;
    M->data[2].e = 5;

    M->data[3].i = 2;
    M->data[3].j = 2;
    M->data[3].e = -1;

    M->data[4].i = 3;
    M->data[4].j = 1;
    M->data[4].e = 2;

    M->rpos[1] = 1;
    M->rpos[2] = 3;
    M->rpos[3] = 4;
}

Status CreateTSMatrix_AUTO(RLSMatrix *M)
{
    M->mu = 4;
    M->nu = 2;
    M->tu = 4;
    M->data[1].i = 1;
    M->data[1].j = 2;
    M->data[1].e = 2;

    M->data[2].i = 2;
    M->data[2].j = 1;
    M->data[2].e = 1;

    M->data[3].i = 3;
    M->data[3].j = 1;
    M->data[3].e = -2;

    M->data[4].i = 3;
    M->data[4].j = 2;
    M->data[4].e = 4;

    M->rpos[1] = 1;
    M->rpos[2] = 2;
    M->rpos[3] = 3;
    M->rpos[4] = 5;
}

Status PrintTSMatrix(RLSMatrix M)
{
    int k;

    printf(" i  j  v\n");
    for(k = 1;k<= M.tu;k++)
        printf("%2d %2d %2d\n",M.data[k].i,M.data[k].j,M.data[k].e);
}

Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
{
    int arow,brow,ccol,i,tp,p,q,tq,ctemp[N.nu+1];
    if(M.nu != N.mu)
        return ERROR;
    (*Q).mu = M.mu;
    (*Q).nu = N.nu;
    Q->tu = 0;
    if(M.tu * N.tu){  //Q是非零矩阵
        for(arow = 1;arow <= M.mu;++arow){ //处理M的每一行

            for(ccol = 0;ccol<=N.nu;++ccol)
                ctemp[ccol] = 0;//当前行各元素累加器清零

            (*Q).rpos[arow] = (*Q).tu + 1;

            if(arow < M.mu)
               tp = M.rpos[arow + 1];
            else
               tp = M.tu + 1;

            for(p = M.rpos[arow]; p<tp;++p){  //对当前行中每一个非零元
                brow = M.data[p].j;  //找到对应元在N中的行号

                if(brow < N.mu)
                    tq = N.rpos[brow + 1];
                else
                    tq = N.tu + 1;

                for(q = N.rpos[brow];q < tq;++q){
                    ccol = N.data[q].j;
                    ctemp[ccol] += M.data[p].e * N.data[q].e;
                }//for q
            }//求得Q中第crow（=arow）行的非零元

            if(ctemp[ccol]){
                ++Q->tu;
                (*Q).data[(*Q).tu].i = arow;
                (*Q).data[(*Q).tu].j = ccol;
                (*Q).data[(*Q).tu].e = ctemp[ccol];
            }//if
        }//for arow
    }//if
    return OK;
}
/*******************************主函数部分**************************************/
int main()
{
    RLSMatrix M,N,Q;
    CreateTSMatrix(&M);
    printf("M矩阵的三元组表示为：\n");
    PrintTSMatrix(M);

    printf("\nN矩阵的三元组表示为：\n");
    CreateTSMatrix_AUTO(&N);
    PrintTSMatrix(N);

    printf("\nQ = M * N 的三元组为：\n");
    MultSMatrix(M,N,&Q);
    PrintTSMatrix(Q);
    return 0;
}



