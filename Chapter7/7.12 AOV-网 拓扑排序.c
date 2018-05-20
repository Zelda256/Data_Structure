#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef char InfoType;
typedef int VertexType;

#define MAX_VERTEX_NUM 20
typedef struct ArcNode
{
    int adjvex;  //该弧所指向的顶点的位置
    struct ArcNode *nextarc;  //指向下一条弧的指针
    InfoType *info;  //该弧相关信息的指针
}ArcNode;
typedef struct VNode
{
    VertexType data;   //顶点信息
    ArcNode *firstarc;   //指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;  //图的当前顶点数和弧数
    int kind;  //图的种类标志
}ALGraph;  //Adjacency List Graph   邻接表

typedef int SElemType;
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
Status Push(SqStack *S,SElemType e);
//插入元素e为新的栈顶元素
Status Pop(SqStack *S,SElemType *e);
//若栈不空，则删除S的栈顶元素，用e返回其值
Status StackEmpty(SqStack S);
//若栈S为空，则返回TRUE，否则FALSE
Status CreateALGraph(ALGraph *G);
//创建邻接表方式存储的有向图
int LocateVex(ALGraph G,VertexType v);
//确定v在G中的位置
Status TopologicalSort(ALGraph G);
//若G无回路，输出G的顶点的一个拓扑序列并返回OK，否则ERROR
Status FindInDegree(ALGraph G,int indegree[]);
//对各顶点求入度indegree[0...vernum-1]
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

Status StackEmpty(SqStack S)
{
    return S.base == S.top ? TRUE : FALSE;
}

Status CreateALGraph(ALGraph *G)
{
    printf("开始创建有向图\n");
    int i,j,k;
    VertexType v1,v2;
    ArcNode *r[MAX_VERTEX_NUM+1];

    printf("\n请输入顶点个数：");
    scanf("%d",&(*G).vexnum);
    printf("请输入弧个数：");
    scanf("%d",&(*G).arcnum);
    //假定该图不含其他信息
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //构造顶点向量
        printf("请输入G..vertices[%d].data = ",i);
        scanf("%d",&(*G).vertices[i].data);
        (*G).vertices[i].firstarc = NULL;
        r[i] = NULL;
    } //for

    for(k = 0;k<(*G).arcnum;k++){
        printf("请输入弧头(初始点)：");  //输入一条弧的始点和终点
        scanf("%d",&v1);
        printf("请输入弧尾(终端点)：");
        scanf("%d",&v2);
        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i<0 || j<0)
            return ERROR;
        ArcNode *p;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = NULL;

        if(r[i] == NULL)    //邻接表中第一个结点
            (*G).vertices[i].firstarc = p;   //加入到邻接表
        else
            r[i]->nextarc = p;
        r[i] = p;
    }
    return OK;
}

Status CreateALGraph_auto(ALGraph *G)
{
    printf("开始创建有向图\n");
    int i,j,k;
    VertexType v1,v2;
    ArcNode *r[MAX_VERTEX_NUM+1];
    int v1_list[8] = {1,1,1,3,3,4,6,6};
    int v2_list[8] = {2,4,3,2,5,5,4,5};

    (*G).vexnum = 6;
    (*G).arcnum = 8;
    //假定该图不含其他信息
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //构造顶点向量
        (*G).vertices[i].data = i+1;
        (*G).vertices[i].firstarc = NULL;
        r[i] = NULL;
    } //for

    for(k = 0;k<(*G).arcnum;k++){
        v1 = v1_list[k];
        v2 = v2_list[k];
        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i<0 || j<0)
            return ERROR;
        ArcNode *p;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = NULL;

        if(r[i] == NULL)    //邻接表中第一个结点
            (*G).vertices[i].firstarc = p;   //加入到邻接表
        else
            r[i]->nextarc = p;
        r[i] = p;
    }
    return OK;
}

int LocateVex(ALGraph G,VertexType v)
{
    int ct;
    for(ct = 0;ct < G.vexnum;ct++)
        if(G.vertices[ct].data == v)
            return ct;
    return -1;
}

Status TopologicalSort(ALGraph G)
{
    SqStack S;
    int i,count,k;
    int indegree[MAX_VERTEX_NUM];
    ArcNode *p;

    FindInDegree(G,indegree);  //对各顶点求入度
    InitStack(&S);

    for(i = 0;i<G.vexnum;++i)  //建0入度栈顶S
        if(!indegree[i])   //入度为0者进栈
            Push(&S,i);
    count = 0;  //对输出顶点计数
    while(!StackEmpty(S)){
        Pop(&S,&i);
        printf("%d,%d\n",i,G.vertices[i].data);
        ++count;  //输出i号顶点并计数
        for(p = G.vertices[i].firstarc; p ;p = p->nextarc){
            k = p->adjvex;   //对i号顶点的每个邻接点的入度-1
            if(!(--indegree[k]))
                Push(&S,k);  //若入度为0，则入栈
        }//for
    }//while
    if(count < G.vexnum)
    {
        printf("该有向图有回路\n");
        return ERROR;  //该有向图有回路
    }
    else
        return OK;
}

Status FindInDegree(ALGraph G,int indegree[])
{
    int i,n = G.vexnum,j;
    ArcNode *p;
    for(i = 0;i<n;i++)
        indegree[i] = 0;
    for(i = 0;i<n;i++){
        p = G.vertices[i].firstarc;
        while(p){
            indegree[p->adjvex]++;
            p = p->nextarc;
        }//while
    }//for
    return OK;
}

/*******************************主函数部分**************************************/
int main()
{
    ALGraph G;
    printf("P182,图7.28 (a)\n");
    CreateALGraph_auto(&G);
    printf("输出拓扑有序序列及该点保存的值为：\n");
    TopologicalSort(G);
    return 0;
}
