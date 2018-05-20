#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAX_TREE_SIZE 100
typedef int Status;
typedef char TElemType;

typedef struct PTNode  //结点结构
{
    TElemType data;
    int parent;   //双亲位置域
}PTNode;
typedef struct  //树结构
{
    PTNode nodes[MAX_TREE_SIZE];
    int r,n;  //跟的位置和结点数
}PTree;

typedef PTree MFSet;

/*******************************声明部分****************************************/
Status find_mfset(MFSet S,int i);
//找集合S中i所在子集的根
Status merge_mfset(MFSet *S, int i,int j);
//S.nodes[i]和S.nodes[j]分别为S的互不相交的两个子集Si和Sj的根结点
//并求交集Si ∪ Sj
Status mix_mfset(MFSet *S,int i,int j);
//S.nodes[i]和S.nodes[j]分别为S的互不相交的两个子集Si和Sj的根结点
//并求交集Si ∪ Sj
int fix_mfset(MFSet *S,int i);
//确定j所在子集，并将从i至根路径上所有结点都编程根的孩子结点
Status CreateMFSet(MFSet *S);
//将创建如书上P135 图6.13 的树。
/*******************************函数部分****************************************/

Status find_mfset(MFSet S,int i)
{
    if(i<1 || i>S.n)
        return -1;  //i不属于S中任一子集
    int ct;
    for(ct = i;S.nodes[ct].parent > 0;ct = S.nodes[ct].parent);
    return ct;
}

Status merge_mfset(MFSet *S, int i,int j)
{
    if(i<1 || i>(*S).n || j<1 || j>(*S).n)
        return ERROR;
    (*S).nodes[i].parent = j;
    return OK;
}

Status mix_mfset(MFSet *S,int i,int j)
{
    if(i<1 || i>(*S).n || j<1 || j>(*S).n)
        return ERROR;
    if((*S).nodes[i].parent > (*S).nodes[j].parent){
        (*S).nodes[j].parent += (*S).nodes[i].parent;
        (*S).nodes[i].parent = j;
    }
    else{
        (*S).nodes[i].parent += (*S).nodes[j].parent;
        (*S).nodes[j].parent += i;
    }
    return OK;
}

int fix_mfset(MFSet *S,int i)
{
    int j,k,t;
    if(i<1 || i>(*S).n)
        return -1;
    for(j = i;(*S).nodes[j].parent>0;j = (*S).nodes[j].parent);

    for(k = i;k != j;k = t){
        t = (*S).nodes[k].parent;
        (*S).nodes[k].parent = j;
    }
    return j;
}

Status CreateMFSet(MFSet *S)
{
    printf("将创建如书上P135 图6.13 的树。\n");
    (*S).r = 0;
    (*S).n = 0;  //初始化为零，后续逐渐增加
    int ct;
    for(ct = 0;ct < 10;ct++){
        printf("\n输入数组下标为 %d 的结点存放的字符：\n",ct);
        scanf("%s",&(*S).nodes[ct].data);

        printf("\n请输入该结点的双亲位置域：\n");
        scanf("%d",&(*S).nodes[ct].parent);
        (*S).n++;
    }
    return OK;
}

Status CreateMFSet_auto(MFSet *S)
{
    char ch1;
    char ch1_list[10] = {'R','A','B','C','D','E','F','G','H','K'};
    int pos;
    int pos_list[10] = {-1,0,0,0,1,1,3,6,6,6};

    printf("自动创建如书上P135 图6.13 的树。\n");
    (*S).r = 0;
    (*S).n = 0;  //初始化为零，后续逐渐增加
    int ct;
    for(ct = 0;ct < 10;ct++){
        ch1 = ch1_list[ct];
        (*S).nodes[ct].data = ch1;

        pos = pos_list[ct];
        (*S).nodes[ct].parent = pos;
        (*S).n++;
    }
    return OK;
}

/*******************************主函数部分**************************************/
int main()
{
    MFSet S;
    CreateMFSet_auto(&S);
    int j = find_mfset(S,4);
    printf("在集合S中4所在子集的根为：%d\n",j);
    return 0;
}
