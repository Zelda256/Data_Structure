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

typedef int Status;
typedef int ElemType;

typedef struct OLNode
{
    int i,j;   //该非零元的行和列下标
    ElemType e;
    struct OLNode *right,*down;  //该非零元所在行表和列表的后继链域
}OLNode, *OLink;
typedef struct
{
    OLink *rhead,*chead;  //行和列链表头指针向量基址由CreateSMatrix分配
    int mu,nu,tu;   //稀疏矩阵的行数、列数和非零元个数
}CrossList;  //十字链表


/*******************************声明部分****************************************/
Status CreateSMatrix_OL(CrossList *M);
//创建十字链表
Status PrintSMatrix_OL(CrossList M);
//输出十字链表
/*******************************函数部分****************************************/
Status CreateSMatrix_OL(CrossList *M)
{
    int m,n,t,k,i,j,e;
    if(M)
        free(M);
    printf("请输入矩阵的行数：");
    scanf("%d",& m);
    printf("请输入矩阵的列数：");
    scanf("%d",& n);
    printf("请输入矩阵的非零元个数：");
    scanf("%d",& t);
    M->mu = m;
    M->nu = n;
    M->tu = t;

    if(!(M->rhead = (OLink *)malloc((m+1)*sizeof(OLink))))
        exit(OVERFLOW);
    if(!(M->chead = (OLink *)malloc((n+1)*sizeof(OLink))))
        exit(OVERFLOW);

    for(k = 0;k<= M->mu;k++)  //初始化行列头指针向量；各行列链表为空链表
        M->rhead[k] = NULL;
    for(k = 0;k<= M->nu;k++)
        M->chead[k] = NULL;
    for(k = 1;k<= M->tu;k++){
        printf("请输入第 %d 个非零元的信息\n",k);
        printf("请输入行号：\n");
        scanf("%d",&i);
        printf("请输入列号\n");
        scanf("%d",&j);
        printf("请输入值：\n");
        scanf("%d",&e);

        OLNode *p,*q;
        p = (OLNode *)malloc(sizeof(OLNode));  //生成结点
        p->i = i;
        p->j = j;
        p->e = e;

        if(M->rhead[i] == NULL || M->rhead[i]->j > j){
            p->right = M->rhead[i];
            M->rhead[i] = p;
        }//if
        else{  //寻查在行表中的插入位置
            for(q = M->rhead[i];(q->right) && q->right->j < j;q = q->right);
            p->right = q->right;
            q->right = p;  //完成行插入
        }//else

        if(M->chead[j] == NULL || M->chead[j]->i > i){
            p->down = M->chead[j];
            M->chead[j] = p;
        }//if
        else{  //寻查在列表中的插入位置
            for(q = M->chead[j];(q->down) && q->down->i < i;q = q->down);
            p->down = q->down;
            q->down = p;  //完成列插入
        }//else
    }//for
    return OK;
}

Status CreateSMatrix_OL_auto(CrossList *M)
{
    int m,n,t,k,i,j,e;
    int i_list[4] = {1,1,2,3};
    int j_list[4] = {1,4,2,1};
    int e_list[4] = {3,5,-1,2};

    if(M)
        free(M);
    m = 3;
    n = 4;
    t = 4;
    M->mu = m;
    M->nu = n;
    M->tu = t;

    if(!(M->rhead = (OLink *)malloc((m+1)*sizeof(OLink))))
        exit(OVERFLOW);
    if(!(M->chead = (OLink *)malloc((n+1)*sizeof(OLink))))
        exit(OVERFLOW);
    for(k = 0;k<= M->mu;k++)  //初始化行列头指针向量；各行列链表为空链表
        M->rhead[k] = NULL;
    for(k = 0;k<= M->nu;k++)
        M->chead[k] = NULL;
    for(k = 1;k<= M->tu;k++){
        i = i_list[k-1];
        j = j_list[k-1];
        e = e_list[k-1];
        OLNode *p,*q;
        p = (OLNode *)malloc(sizeof(OLNode));  //生成结点
        p->i = i;
        p->j = j;
        p->e = e;

        if(M->rhead[i] == NULL || M->rhead[i]->j > j){
            p->right = M->rhead[i];
            M->rhead[i] = p;
        }//if
        else{  //寻查在行表中的插入位置
            for(q = M->rhead[i];(q->right) && q->right->j < j;q = q->right);
            p->right = q->right;
            q->right = p;  //完成行插入
        }//else

        if(M->chead[j] == NULL || M->chead[j]->i > i){
            p->down = M->chead[j];
            M->chead[j] = p;
        }//if
        else{  //寻查在列表中的插入位置
            for(q = M->chead[j];(q->down) && q->down->i < i;q = q->down);
            p->down = q->down;
            q->down = p;  //完成列插入
        }//else
    }//for
    return OK;
}

Status PrintSMatrix_OL(CrossList M)
{
    int i,j;
    OLNode *p;
    for(i = 1;i<= M.mu;i++){
        p = M.rhead[i];
        for(j = 1;j<=M.nu;j++){
            if(p && p->j == j){
                printf("%2d",p->e);
                p = p->right;
            }
            else
                printf(" 0 ");
        }
        printf("\n");
    }
}
/*******************************主函数部分**************************************/
int main()
{
    CrossList M;

    printf("创建十字链表：\n");
    CreateSMatrix_OL_auto(&M);
    PrintSMatrix_OL(M);
    return 0;
}
