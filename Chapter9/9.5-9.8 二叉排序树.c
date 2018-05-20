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
typedef int KeyType;

typedef struct
{
    KeyType key;
    int weight;
}ElemType;
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild,*rchild;  //左孩子右孩子指针
}BiTNode,*BiTree,*Position;


/*******************************声明部分****************************************/
Status InitBiTree(BiTree *T);
BiTree SerchBST_a(BiTree T,KeyType key);
//在根指针T所指二叉排序树中递归查找某关键字等于key的数据元素
Status SerchBST_b(BiTree T,KeyType key,BiTree f,BiTree *p);
//在根指针T所指二叉排序树中递归查找某关键字等于key的数据元素，若查找成功
//则指针p指向该数据元素结点，并返回TRUE，否则指针p指向查找路径上访问的最后一个结点并返回FALSE
//指针f指向T的双亲，其初始调用值为NULL
Status InsertBST(BiTree *T,ElemType e);
//当二叉排序树T中不存在关键字等于e.key的数据元素时，插入e并返回TRUE
Status PreOrderTraverse(BiTree T,Status(*Visit)(ElemType e));
Status Visit(ElemType e);
Status DeleteBST(BiTree *T, KeyType key);
//若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点
Status Delete(BiTree *p);
//从二叉排序树中删除结点p，并重新连接它的左或右子树
/*******************************函数部分****************************************/
Status InitBiTree(BiTree *T)
{
    *T = NULL;
    return OK;
}

BiTree SerchBST_a(BiTree T,KeyType key)
{
    if((!T) || EQ(key,T->data.key))
        return T;  //查找结束
    else if(LT(key,T->data.key))
        return (SerchBST_a(T->lchild,key));  //在左子树中继续查找
    else
        return(SerchBST_a(T->rchild,key));  //在右子树中继续查找
}

Status SerchBST_b(BiTree T,KeyType key,BiTree f,BiTree *p)
{
    if(!T){  //查找不成功
        *p = f;
        return FALSE;
    }
    else if(EQ(key,T->data.key)){  //查找成功
        *p = T;
        return TRUE;
    }
    else if(LT(key,T->data.key))
        return (SerchBST_b(T->lchild,key,T,p));  //在左子树中继续查找
    else
        return (SerchBST_b(T->rchild,key,T,p));  //在右子树中继续查找
}

Status InsertBST(BiTree *T,ElemType e)
{
    BiTree p,s;
    if(!SerchBST_b(*T,e.key,NULL,&p)){  //查找不成功
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data = e;
        s->lchild = s->rchild = NULL;
        if(!p)
            *T = s;  //被插结点*s为新的根结点
        else if(LT(e.key,p->data.key))
            p->lchild = s;  //被插结点*s为左孩子
        else
            p->rchild = s;  //被插结点*s为右孩子
        return TRUE;
    }//IF
    else
        return FALSE;
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

Status InOrderTraverse(BiTree T,Status(*Visit)(ElemType e))  //递归
{
    if(T){
        if(InOrderTraverse(T->lchild,Visit))
            if(Visit(T->data))
                if(InOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status Visit(ElemType e)
{
    printf("%d ",e);
    return OK;
}

Status DeleteBST(BiTree *T, KeyType key)
{
    if(!T)
        return FALSE;
    if(EQ(key,(*T)->data.key))  //找到
        return Delete(T);
    else if(LT(key,(*T)->data.key))
        return DeleteBST(&(*T)->lchild,key);
    else
        return DeleteBST(&(*T)->rchild,key);
}

Status Delete(BiTree *p)
{
    BiTree q,s;
    if(!(*p)->rchild){  //右子树空，秩序重接它的左子树
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    else if(!(*p)->lchild){  //左子树空，秩序重接它的右子树
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else{  //左右子树均不空
        q = *p;
        s = (*p)->lchild;
        while(s->rchild){  //转左，然后向右到尽头
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data;   //s指向被删结点的前驱
        if(q != *p)
            q->rchild = s->lchild;  //重接*q的右子树
        else
            q->lchild = s->lchild;  //重接*q的左子树
        free(s);

    }
}
/*******************************主函数部分**************************************/
int main()
{
    BiTree T;
    ElemType a,b,c,d,e,f,g;
    a.key = 45;
    b.key = 24;
    c.key = 53;
    d.key = 45;
    e.key = 12;
    f.key = 24;
    g.key = 90;

    printf("\n初始化二叉排序树,设查找的关键字序列为\n45,24,53,45,12,24,90\n");
    InitBiTree(&T);
    InsertBST(&T,a);
    InsertBST(&T,b);
    InsertBST(&T,c);
    InsertBST(&T,d);
    InsertBST(&T,e);
    InsertBST(&T,f);
    InsertBST(&T,g);

    printf("\n前序遍历生成的二叉排序树为：\n");
    PreOrderTraverse(T,Visit);

    printf("\n中序遍历生成的二叉排序树为：\n");
    InOrderTraverse(T,Visit);

    printf("\n\n删除key = 24的元素：\n");
    DeleteBST(&T,24);
    printf("\n前序遍历当前的二叉排序树为：\n");
    PreOrderTraverse(T,Visit);

    printf("\n中序遍历当前的二叉排序树为：\n");
    InOrderTraverse(T,Visit);

    printf("\n");
    return 0;
}



