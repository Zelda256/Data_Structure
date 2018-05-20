#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LIST_INIT_SIZE 100 //存储空间的初始分配量

typedef int Status;
typedef char KeyType;
typedef char TElemType;
typedef struct
{
    KeyType key;
    int weight;
}ElemType;
typedef struct
{
    ElemType *elem; //unit elem[0] keep NULL
    int length;   //length of table
}SSTable;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild,*rchild;  //左孩子右孩子指针
}BiTNode,*BiTree,*Position;

typedef BiTree SOSTree;  //次优查找树采用二叉链表的存储结构
/*******************************声明部分****************************************/
Status InitTable(SSTable *L);
Status CreateTalbe(SSTable *L);
void SecondOpiamal(BiTree *T,ElemType R[],int sw[],int low,int high);
//递归构造次优查找树T
Status CreateSOSTree(SOSTree *T,SSTable ST);
//由有序表ST构造一棵次优查找树T
Status FindSW(int sw[],SSTable ST);
//构造有序表ST的累计权值表sw
Status Visit(ElemType e);
Status PreOrderTraverse(BiTree T,Status(*Visit)(ElemType e));
/*******************************函数部分****************************************/
Status InitTable(SSTable *L)
{
    (*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!(*L).elem)
        exit(OVERFLOW);
    (*L).length = 0;
    return OK;
}

Status CreateTalbe(SSTable *L)
{
    int i;
 /*   printf("请输入顺序表的长度:");
    scanf("%d",&L->length);
    for(i = 1;i<=L->length;i++){
        printf("请输入第 %d 个元素的值：",i);
        scanf("%s",&L->elem[i].key);
        printf("请输入第 %d 个元素的权：",i);
        scanf("%d",&L->elem[i].weight);
    }*/
    L->length = 9;
    L->elem[1].key = 'A';
    L->elem[2].key = 'B';
    L->elem[3].key = 'C';
    L->elem[4].key = 'D';
    L->elem[5].key = 'E';
    L->elem[6].key = 'F';
    L->elem[7].key = 'G';
    L->elem[8].key = 'H';
    L->elem[9].key = 'I';

    L->elem[1].weight = 1;
    L->elem[2].weight = 1;
    L->elem[3].weight = 2;
    L->elem[4].weight = 5;
    L->elem[5].weight = 3;
    L->elem[6].weight = 4;
    L->elem[7].weight = 4;
    L->elem[8].weight = 3;
    L->elem[9].weight = 5;

    return OK;
}

void SecondOpiamal(BiTree *T,ElemType R[],int sw[],int low,int high)
{
    int i,j,min,dw;

    i = low;
    min = abs(sw[high] - sw[low]);
    dw = sw[high]+sw[low-1];
    for(j = low+1;j<=high;j++){
        if( abs(dw-sw[j]-sw[j-1]) < min){
            i = j;
            min = abs(dw-sw[j]-sw[j-1]);
        }
    }//for
    *T = (BiTree)malloc(sizeof(BiTNode));
    (*T)->data = R[i];  //生成结点
    if(i == low)  //左子树空
        (*T)->lchild = NULL;
    else
        SecondOpiamal(&(*T)->lchild,R,sw,low,i-1);  //构造左子树
    if(i == high)
        (*T)->rchild = NULL;
    else
        SecondOpiamal(&(*T)->rchild,R,sw,i+1,high);
}

Status CreateSOSTree(SOSTree *T,SSTable ST)
{
    int sw[ST.length+1];
    if(ST.length == 0)
        *T = NULL;
    else{
        FindSW(sw,ST);
        SecondOpiamal(T,ST.elem,sw,1,ST.length);
    }
    return OK;
}

Status FindSW(int sw[],SSTable ST)
{
    int sum,i;
    sw[0] = 0;
    sum = 0;
    for(i = 1;i<=ST.length;i++){
        sum += ST.elem[i].weight;
        sw[i] = sum;
    }
    printf("sw中的元素为：\n");
    for(i = 0;i<=ST.length;i++)
        printf("%d  ",sw[i]);
    printf("\n");
    return OK;
}

Status Visit(ElemType e)
{
    printf("%c  ",e);
    return OK;
}

Status PreOrderTraverse(BiTree T,Status(*Visit)(ElemType e))  //递归
{
    if(T){
        if(Visit(T->data))
            if(PreOrderTraverse(T->lchild,Visit))
                if(PreOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}
/*******************************主函数部分**************************************/
int main()
{
    SSTable L;
    SOSTree T;

    InitTable(&L);
    CreateTalbe(&L);
    CreateSOSTree(&T,L);
    printf("先序遍历次优二叉树:\n");
    PreOrderTraverse(T,Visit);

    return 0;
}



