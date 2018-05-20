#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define SIZE 100
typedef int Status;
typedef char TElemType;
typedef char SElemType;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild,*rchild;  //左孩子右孩子指针
}BiTNode,*BiTree,*Position;

typedef struct SNode
{
    BiTree data;
    struct SNode *next;
}SNode;
typedef struct
{
    SNode *base;  //在栈构造之前和销毁之后，base的值为NULL
    SNode *top;  //栈顶指针
}SqStack;

/*******************************声明部分****************************************/

Status InitStack(SqStack *S);
//初始化栈
Status Pop(SqStack *S,BiTree *e);
//删除栈顶元素，并用e返回栈顶元素
Status InitBiTree(BiTree *T);
//构造二叉树
Status Push(SqStack *S,BiTree e);
//将元素e压入栈
Status StackEmpty(SqStack S);
//判断是否栈空
Status GetTop(SqStack *S,BiTree *e);
//取栈顶元素，用e返回
Status InitBiTree(BiTree *T);
//构造空二叉树
Status BiTreeEmpty(BiTree T);
//若二叉树T为空，则返回TRUE，否则FALSE
TElemType Root(BiTree T);
//返回T的根
Status CreateBiTree(BiTree *T);
//按先次序输入二叉树中结点的值（一个字符），空格字符表示空树，
//构造二叉链表表示的二叉树T
Status Visit(TElemType e);
Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e));  //递归
//采用二叉链表存储结构，先序递归遍历二叉树T的递归算法
Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e));  //递归
//采用二叉链表存储结构，中序递归遍历二叉树T的递归算法
Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e));  //递归
//采用二叉链表存储结构，后序递归遍历二叉树T的递归算法
Status InOrderTraverse_1(BiTree T); //非递归;
//采用二叉链表存储结构，中序非递归遍历二叉树T的递归算法
Status InOrderTraverse_2(BiTree T); //非递归;
//采用二叉链表存储结构，中序非递归遍历二叉树T的递归算法

/*******************************函数部分****************************************/

Status InitStack(SqStack *S)
{
    S->top = S->base = NULL;
    return OK;
}

Status Pop(SqStack *S,BiTree *e)
{
    if(S->top == S->base)
        return ERROR;
    SNode *p = S->top;
    S->top = S->top->next;
    *e = p->data;
    free(p);
    return OK;
}

Status Push(SqStack *S,BiTree e)
{
    SNode *p = (SNode*)malloc(sizeof(SNode));
    if(!p)
        exit(OVERFLOW);
    p->data = e;
    p->next = S->top;
    S->top = p;
    return OK;
}

Status StackEmpty(SqStack S)
{
    return S.base==S.top;
}

Status GetTop(SqStack *S,BiTree *e)
{
    if((*S).top == NULL)
        return ERROR;
    *e = (*S).top->data;
    return OK;
}

Status InitBiTree(BiTree *T)
{
    *T = NULL;
    return OK;
}

Status BiTreeEmpty(BiTree T)
{
    return T==NULL;
}

Status BiTreeDepth(BiTree T)
{
    int L,R;
    if(T){
        L = BiTreeDepth(T->lchild);
        R = BiTreeDepth(T->rchild);
        return(L > R ? L:R)+1;
    }
    return 0;
}

TElemType Root(BiTree T)
{
    return T->data;
}

Status CreateBiTree(BiTree *T)
{
    TElemType ch;
    //scanf("%c",&ch); //也可以运行
    ch = getchar();
    if(ch == ' ')
        *T = NULL;
    else{
        *T = (BiTree)malloc(sizeof(BiTNode));
        if(!(*T))
            exit(OVERFLOW);
        (*T)->data = ch;  //生成根结点
        CreateBiTree(&(*T)->lchild);  //构造左子树
        CreateBiTree(&(*T)->rchild);  //构造右子树
    }
    return OK;
}

Status Visit(TElemType e)
{
    printf("%c\t",e);
    return OK;
}

Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e))  //递归
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

Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e))  //递归
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

Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e))  //递归
{
    if(T){
        if(PostOrderTraverse(T->lchild,Visit))
            if(PostOrderTraverse(T->rchild,Visit))
                if(Visit(T->data))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status InOrderTraverse_1(BiTree T)  //非递归
{
    SqStack S;
    BiTNode *p;
    InitStack(&S);
    Push(&S,T);  //根指针进栈
    while(!StackEmpty(S)){
        while(GetTop(&S,&p) && p)
            Push(&S,p->lchild);  //向左走到尽头
        Pop(&S,&p);  //空指针退栈
        if(!StackEmpty(S)){  //访问结点，向右一步
            Pop(&S,&p);
            if(!Visit(p->data))
                return ERROR;
            Push(&S,p->rchild);
        }
    }
    return OK;
}

Status InOrderTraverse_2(BiTree T)  //非递归
{
    SqStack S;
    BiTNode *p;
    InitStack(&S);
    p = T;
    while(p || !StackEmpty(S)){
       if(p){
        Push(&S,p);
        p = p->lchild;  //根指针进栈，遍历左子树
       }
       else{  //根指针退栈，访问根结点，遍历右子树
        Pop(&S,&p);
        if(!Visit(p->data))
            return ERROR;
        p = p->rchild;
       }
    }//while
    return OK;
}


/*******************************主函数部分**************************************/

int main()
{
    BiTree T;
    InitBiTree(&T);

    //复制分号前的字符:ABC  DE G  F   ；
    printf("\n创建二叉树(键入ABC^^DE^G^^F^^^,其中'^'表示空格)：\n");
    CreateBiTree(&T);

    printf("\n\n前序遍历：\n");
    PreOrderTraverse(T,Visit);

    printf("\n\n中序遍历：\n");
    InOrderTraverse(T,Visit);

    printf("\n\n后序遍历：\n");
    PostOrderTraverse(T,Visit);

    printf("\n\n中序非递归遍历1：\n");
    InOrderTraverse_1(T);

    printf("\n\n中序非递归遍历2：\n");
    InOrderTraverse_2(T);

    printf("\n");
    return 0;
}
