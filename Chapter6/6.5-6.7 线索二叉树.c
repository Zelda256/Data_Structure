#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef char TElemType;

typedef enum {Link, Thread} PointerTag;   //Link == 0: 指针 ，Thread == 1:线索

typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild, *rchild;  //左右孩子指针
    PointerTag   LTag,RTag;    //左右标志
}BiThrNode, *BiThrTree;

/*******************************声明部分****************************************/

Status Visit(TElemType e);
Status CreateBiTree(BiThrTree *T);
//按先次序输入二叉树中结点的值（一个字符），空格字符表示空树，
//构造二叉链表表示的二叉树T
void InThreading(BiThrTree p);
//将二叉树线索化的辅助函数
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T);
//中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
Status InOrderTraverse_Thr(BiThrTree T,Status(*Visit)(TElemType e));
//T指向头结点，头结点的左链lchild指向根结点
//中序遍历二叉线索树T的非递归算法，对每个数据元素调用Visit函数

/*******************************函数部分****************************************/

Status Visit(TElemType e)
{
    printf("%c\t",e);
    return OK;
}

Status CreateBiTree(BiThrTree *T)
{
    TElemType ch;
  //  scanf("%c",&ch);
    ch = getchar();
    if(ch == ' ')
        *T = NULL;
    else{
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        if(!(*T))
            exit(OVERFLOW);
        (*T)->data = ch;  //生成根结点
        CreateBiTree(&(*T)->lchild);  //构造左子树
        if((*T)->lchild)  //有左孩子
            (*T)->LTag = Link;
        CreateBiTree(&(*T)->rchild);  //构造右子树
        if((*T)->rchild)  //有右孩子
            (*T)->RTag = Link;
    }
    return OK;
}

BiThrTree pre;  //全局变量，始终指向刚刚访问过的结点
void InThreading(BiThrTree p)
{
    if(p){
        InThreading(p->lchild);  //左子树线索化
        if(!p->lchild){  //前驱线索
            p->LTag = Thread;
            p->lchild = pre;
        }
        if(!pre->rchild){  //后继线索
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;
        InThreading(p->rchild);  //右子树线索化
    }
}

Status InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{
    (*Thrt)= (BiThrTree)malloc(sizeof(BiThrNode));
    if(!(*Thrt))
        exit(OVERFLOW);
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;  //建立头结点
    (*Thrt)->rchild = *Thrt;  //右指针回指
    if(!T)
        (*Thrt)->lchild = *Thrt;  //若二叉树空，则左指针回指
    else{
        (*Thrt)->lchild = T;
        pre = *Thrt;
        InThreading(T);  //中序遍历进行中序线索化
        pre->rchild = *Thrt;
        pre->RTag = Thread;   //最后一个结点线索化
        (*Thrt)->rchild = pre;
    }//else
    return OK;
}

Status InOrderTraverse_Thr(BiThrTree T,Status(*Visit)(TElemType e))
{
    BiThrTree p;
    p = T->lchild;   //p指向根结点
    while(p != T){
        //空树或遍历结束时，p == T
        while(p->LTag == Link)
            p = p->lchild;
        if(!Visit(p->data))  //访问其左子树为空的结点
            return ERROR;
        while(p->RTag == Thread && p->rchild != T){
            p = p->rchild;
            Visit(p->data);  //访问后继结点
        }//while
        p = p->rchild;
    }//while
    return OK;
}

/*******************************主函数部分**************************************/

int main()
{
    BiThrTree H,T;

    //复制分号前的字符:ABC  DE G  F   ；
    printf("\n创建二叉树(键入ABC^^DE^G^^F^^^)：\n");
    CreateBiTree(&T);
    InOrderThreading(&H,T);
    printf("\n中序遍历 输出二叉线索树\n");
    InOrderTraverse_Thr(H,Visit);
    printf("\n");

    return 0;
}


