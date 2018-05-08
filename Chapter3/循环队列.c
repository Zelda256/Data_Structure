#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int QElemType;

#define MAXQSIZE 100  //max queue length
typedef struct
{
    QElemType *base;  //初始化的动态分配存储空间
    int front;  //head pointer,若队列不空，指向队列头元素
    int rear;  //tail pointer,若队列不空，指向队列尾元素的下一个位置
}SqQueue;

/*******************************声明部分****************************************/
Status InitQueue(SqQueue *Q);
//构造一个空队列Q
int QueueLength(SqQueue Q);
//返回Q的元素个数，即队列的长度
Status EnQueue(SqQueue *Q,QElemType e);
//插入元素e为Q的新的队尾元素
Status DeQueue(SqQueue *Q,QElemType *e);
//若队列不空，则删除Q的队头元素，用e返回其值
Status TraverseQueue(SqQueue Q);
//输出队列Q中的所有元素
/*******************************函数部分****************************************/
Status InitQueue(SqQueue *Q)
{
    Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if(!Q->base)
        exit(OVERFLOW);
    Q->front = Q->rear = 0;
    return OK;
}

int QueueLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}

Status EnQueue(SqQueue *Q,QElemType e)
{
    if((Q->rear+1)%MAXQSIZE==Q->front)
        return ERROR;
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear+1)%MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue *Q,QElemType *e)
{
    if(Q->front == Q->rear)
        return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front+1)%MAXQSIZE;
    return OK;
}

Status TraverseQueue(SqQueue Q)
{
    if(Q.front == Q.rear){
        printf("队列为空\n");
        return ERROR;
    }
    int i = Q.front;
    while(i%MAXQSIZE != Q.rear)
        printf("%d ",Q.base[i++]);
    printf("\n");
    return OK;
}
/*******************************主函数部分**************************************/

int main()
{
    SqQueue Q;
    QElemType e;

    printf("初始化一个空队列：\n");
    InitQueue(&Q);
    TraverseQueue(Q);

    printf("\n构造队列 1...10 ：\n");
    int i;
    for(i = 1;i<=10;++i)
        EnQueue(&Q,i);
    TraverseQueue(Q);

    printf("\n在队列尾插入元素 13 ：\n");
    EnQueue(&Q,13);
    TraverseQueue(Q);

    printf("\n删除队头元素，用e返回该删除值：\n");
    DeQueue(&Q,&e);
    TraverseQueue(Q);
    printf("被删除的元素 e = %d\n",e);

    printf("\n任意键退出...\n");
    _getch();
    return 0;
}


