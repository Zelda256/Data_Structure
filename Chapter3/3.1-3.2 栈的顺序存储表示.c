//3.1-3.2 栈的顺序存储表示.c
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
//typedef int SElemType;
typedef char SElemType;
#define STACK_INIT_SIZE 100  //存储空间初始分配量
#define STACKINCREMENT 10  //存储空间分配增量

typedef struct
{
    SElemType *base;  //在栈构造之前和销毁之后，base的值为NULL
    SElemType *top;  //栈顶指针
    int stacksize;  //当前已分配的存储空间，以元素为单位
}SqStack;

/*******************************声明部分****************************************/
Status InitStack(SqStack *S);
//构造一个空栈S
Status GetTop(SqStack S,SElemType *e);
//若栈不空，则用e返回S的栈顶元素
Status Push(SqStack *S,SElemType e);
//插入元素e为新的栈顶元素
Status Pop(SqStack *S,SElemType *e);
//若栈不空，则删除S的栈顶元素，用e返回其值
int StackLength(SqStack S);
//返回S的元素个数，即栈长
Status StackEmpty(SqStack S);
//若栈S为空，则返回TRUE，否则FALSE
void conversion();
//对于输入任意一个非负十进制整数，打印输出其八进制数
void ClearStack(SqStack *S);
//把S置为空栈
/*******************************函数部分****************************************/

Status InitStack(SqStack *S)
{
    (*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!(*S).base)
        exit(OVERFLOW);
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S,SElemType *e)
{
    if(S.top == S.base)
        return ERROR;
    *e = *(S.top-1);
    return OK;
}

Status Push(SqStack *S,SElemType e)
{
    if((*S).top - (*S).base >= (*S).stacksize){  //栈满，追加空间
        (*S).base = (SElemType *)realloc((*S).base,((*S).stacksize + STACKINCREMENT)* sizeof(SElemType));
    if( !(*S).base)
        exit(OVERFLOW);
    (*S).top = (*S).base + (*S).stacksize;
    (*S).stacksize += STACKINCREMENT;
    }
    *(*S).top++ = e;
    return OK;
}

Status Pop(SqStack *S,SElemType *e)
{
    if((*S).top == (*S).base)
        return ERROR;
    *e = *--(*S).top;
    return OK;
}

int StackLength(SqStack S)
{
    return S.top-S.base;
}

void Visit(SElemType e)
{
    printf("%d->",e);
}

void StackTraverse(SqStack S)
{
    while(S.base != S.top){
        S.top--;
        Visit(*S.top);
    }
}

Status StackEmpty(SqStack S)
{
    return S.base == S.top ? TRUE : FALSE;
}

void conversion()
{
    SqStack L;
    SElemType e;
    int N;
    InitStack(&L);
    printf("\n\n请输入一位非负十进制整数,程序返回其八进制：\n");
    scanf("%d",&N);
    while(N){
        Push(&L,N%8);
        N = N/8;
    }
    while(!StackEmpty(L)){
        Pop(&L,&e);
        printf("%d",e);
    }
    printf("\n");
}

void ClearStack(SqStack *S)
{
    while((*S).base != (*S).top )
        (*S).top--;
    (*S).stacksize = 0;
}
void LineEdit()
{
    SqStack L;
    char c,ch,*p;
    InitStack(&L);  //构造空栈
    printf("输入：");
    ch = getchar();  //从终端接收第一个字符
    while(ch != EOF){
        printf("输出：");
        while(ch != EOF && ch != '\n'){
            switch(ch)
            {
                case '#':
                    Pop(&L,&c);
                    break;
                case '@':
                    ClearStack(&L);
                    break;
                default :
                    Push(&L,ch);
                    break;
            }//switch
            ch = getchar();  //从终端接收下一个字符
        }//while
    p = L.base;
    while(p != L.top){
        printf("%c",*p);
        ++p;
    }
    printf("\n");
    ClearStack(&L);
    if(ch != EOF)
        printf("输入：");
        ch = getchar();
    }
}
/*******************************主函数部分**************************************/
/*
int main()
{
    SqStack S;
    InitStack(&S);
    int ct;
    for(ct = 1;ct <= 5;ct++)
        Push(&S,ct);
    printf("当前栈的元素如下：\n");
    StackTraverse(S);

    SElemType e;
    GetTop(S,&e);
    printf("\n当前的栈顶元素为： %d\n",e);

    Pop(&S,&e);
    printf("\n删除栈顶元素后：\n");
    StackTraverse(S);

    conversion();
}*/
int main()
{
    //whli##ilr#e(s#*s)
    //outcha@putchar(*s=#++);
    LineEdit();
    return 0;
}



