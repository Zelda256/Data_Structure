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
#define LH +1  //左高
#define EH 0  //登高
#define RH -1  //右高

typedef int Status;
typedef int KeyType;
typedef struct
{
    KeyType key;
    int weight;
}ElemType;
typedef struct BSTNode
{
    ElemType data;
    int bf;    //结点的平衡因子
    struct BSTNode *lchild,*rchild;  //左孩子右孩子指针
}BSTNode,*BSTree;
typedef struct
{
    ElemType *elem; //unit elem[0] keep NULL
    int length;   //length of table
}SSTable;
/*******************************声明部分****************************************/
void R_Rotate(BSTree *p);
//对以*p为根的二叉排序树作右旋处理，处理之后dp指向新的树根节点，
//即旋转之前的左子树的根结点
void L_Rotate(BSTree *p);
//对以*p为根的二叉排序树作左旋处理，处理之后dp指向新的树根节点，
//即旋转之前的右子树的根结点
void LeftBalance(BSTree *T);
//对以指针T所指结点为根的二叉树左平衡旋转处理，本算法结束时，T指向新的根结点
Status InsertAVL(BSTree *T,ElemType e,int *taller);
//若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个数据元素为e
//的新结点，并返回1，否则返回0.因插入而使得二叉排序树失去平衡，则作平衡旋转处理，
//taller反应树长高与否
Status CreateTalbe(SSTable *L);
Status InitTable(SSTable *L);
Status Visit(ElemType e);
Status PreOrderTraverse(BSTree T,Status(*Visit)(ElemType e));
/*******************************函数部分****************************************/
void R_Rotate(BSTree *p)
{
    BSTree lc;
    lc = (*p)->lchild;  //lc指向*p的左子树根结点
    (*p)->lchild = lc->rchild;  //lc的右子树挂接为*p的左子树
    lc->rchild = *p;  //p指向新的根结点
    *p = lc;
}

void L_Rotate(BSTree *p)
{
    BSTree rc;
    rc = (*p)->rchild;  //lc指向*p的左子树根结点
    (*p)->rchild = rc->lchild;  //lc的右子树挂接为*p的左子树
    rc->lchild = *p;  //p指向新的根结点
    *p = rc;
}

void LeftBalance(BSTree *T)
{
    BSTree lc,rd;
    lc = (*T)->lchild;  //lc指向*T的左子树根结点
    switch(lc->bf)   //检查*T的左子树平衡度，并作相应平衡处理
    {
    case LH:  //新结点插入在*T的左孩子的左子树上，要做单右旋处理
        (*T)->bf = lc->bf = EH;
        R_Rotate(T);
        break;
    case RH:  //新结点插入在*T的左孩子的右子树上，要作双旋处理
        rd = lc->rchild;   //rd指向*T的左孩子的右子树根
        switch(rd->bf)  //修改*T及其左孩子的平衡因子
        {
        case LH:
            (*T)->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            (*T)->bf = lc->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            lc->bf = LH;
            break;
        }//switch(lc->bf)
        rd->bf = EH;
        L_Rotate(&(*T)->lchild);  //对*T的左子树作左平衡旋转处理
        R_Rotate(T);  //对*T作右旋平衡处理
        break;
    }//switch(lc->bf)
}

void RightBalance(BSTree *T)
{
    BSTree rc,ld;
    rc = (*T)->rchild;
    switch(rc->bf)
    {
    case RH:
        (*T)->bf = rc->bf = EH;
        L_Rotate(T);
        break;

    case LH:
        ld = rc->lchild;
        switch(ld->bf)
        {
        case LH:
            (*T)->bf = EH;
            rc->bf = RH;
            break;
        case EH:
            (*T)->bf = rc->bf = EH;
            break;
        case RH:
            (*T)->bf = LH;
            rc->bf = EH;
            break;
        }
        ld->bf = EH;
        R_Rotate(&(*T)->rchild);
        L_Rotate(T);
        break;
    }
}

Status InsertAVL(BSTree *T,ElemType e,int *taller)
{
    if(!(*T)){          //insert new node,the tree turns taller,set taller = 1
        *T = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = 1;
    }
    else{
        if(EQ(e.key,(*T)->data.key)){  //the tree already has a node == e
            *taller = 0;  //no need to insert
            return 0;
        }
        if(LT(e.key,(*T)->data.key)){  //continue search in lchild
            if(!InsertAVL(&(*T)->lchild,e,taller))
                return 0;  //uninsert
            if(*taller)   //had inserted in lchild,and lchild turns taller
                switch((*T)->bf)   //check if balance
                {
                case LH:    //before,lchild taller than rchild,need leftbalance
                    LeftBalance(T);
                    *taller = 0;
                    break;
                case EH:   //before,lchild the same tall as rchild,now the whole tree turns taller
                    (*T)->bf = LH;
                    *taller = 1;
                    break;
                case RH:  //before,rchild taller than lchild,now the same tall
                    (*T)->bf = EH;
                    *taller = 0;
                    break;
                }//switch t->bf
        }//if
        else{
            if(!InsertAVL(&(*T)->rchild,e,taller))  //continue search in rchild
                return 0;  //uninsert
            if(*taller)   //had inserted in rchild,and rchild turns taller
                switch((*T)->bf)   //check if balance
                {
                case LH:  //before,rchild taller than lchild,now the same tall
                    (*T)->bf = EH;
                    *taller = 0;
                    break;
                case EH:   //before,lchild the same tall as rchild,now the whole tree turns taller
                    (*T)->bf = RH;
                    *taller = 1;
                    break;
                case RH:
                    RightBalance(T);    //before,rchild taller than lchild,need rightbalance
                    *taller = 0;
                    break;
                }//switch T->fb
        }//else
    }//else
    return 1;
}

Status CreateTalbe(SSTable *L)
{
  /*  int i;
    printf("请输入顺序表的长度:");
    scanf("%d",&L->length);
    for(i = 1;i<=L->length;i++){
        printf("请输入第 %d 个元素的值：",i);
        scanf("%d",&L->elem[i].key);
    }*/
    L->length = 5;
    L->elem[1].key = 13;
    L->elem[2].key = 24;
    L->elem[3].key = 37;
    L->elem[4].key = 90;
    L->elem[5].key = 53;

    return OK;
}

Status InitTable(SSTable *L)
{
    (*L).elem = (ElemType *)malloc(100 * sizeof(ElemType));
    if(!(*L).elem)
        exit(OVERFLOW);
    (*L).length = 0;
    return OK;
}

Status Visit(ElemType e)
{
    printf("%d\t",e.key);
    return OK;
}

Status PreOrderTraverse(BSTree T,Status(*Visit)(ElemType e))  //递归
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
    BSTree T;
    SSTable L;
    int i,taller;

    InitTable(&L);
    CreateTalbe(&L);

    taller = 0;
    T = NULL;
    printf("对平衡二叉树插入如下元素：\n");
    for(i = 1;i<=L.length;i++){
        printf("%d ",L.elem[i].key);
        InsertAVL(&T,L.elem[i],&taller);
    }

    printf("\n\n先序遍历插入完成的平衡二叉树为：\n");
    PreOrderTraverse(T,Visit);
    return 0;
}



