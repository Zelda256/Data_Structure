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
typedef int InfoType;
typedef int VertexType;

#define MAX_VERTEX_NUM 20
typedef struct ArcNode
{
    int adjvex;  //该弧所指向的顶点的位置
    struct ArcNode *nextarc;  //指向下一条弧的指针
    int info;  //该弧相关信息的指针 //权重
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

int ve[MAX_VERTEX_NUM];
int vl[MAX_VERTEX_NUM];
/*******************************声明部分****************************************/
Status InitStack(SqStack *S);
//构造一个空栈S
Status Push(SqStack *S,SElemType e);
//插入元素e为新的栈顶元素
Status Pop(SqStack *S,SElemType *e);
//若栈不空，则删除S的栈顶元素，用e返回其值
Status StackEmpty(SqStack S);
//若栈S为空，则返回TRUE，否则FALSE
int LocateVex(ALGraph G,VertexType v);
//确定v在G中的位置
Status CreateALGraph(ALGraph *G);
//创建有向网
Status FindInDegree(ALGraph G,int indegree[]);
//对各顶点求入度indegree[0...vernum-1]
Status TopologicalSort(ALGraph G,SqStack *T);
//有向网G采用邻接表存储结构，求各顶点事件的最早发生时间ve(全局变量)
//T为拓扑序列顶点栈，S为零入度顶点栈
//若G无回路，则用栈T返回G的一个拓扑序列，且函数值为OK，否则为ERROR
Status CriticalPath(ALGraph G);
//G为有向网，输出G的各项关键活动
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

Status CreateALGraph(ALGraph *G)
{
    printf("开始创建有向网\n");
    int i,j,k,w;
    VertexType v1,v2;

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
    } //for

    for(k = 0;k<(*G).arcnum;k++){
        printf("请输入弧头(初始点)：");  //输入一条弧的始点和终点
        scanf("%d",&v1);
        printf("请输入弧尾(终端点)：");
        scanf("%d",&v2);
        printf("请输入权重：");
        scanf("%d",&w);
        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i<0 || j<0)
            return ERROR;

        ArcNode *p;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = (*G).vertices[i].firstarc;
        (*G).vertices[i].firstarc = p;

        p->info = w;
    }
    return OK;
}

Status CreateALGraph_auto(ALGraph *G)
{
    printf("开始创建有向网\n");
    int i,j,k,w;
    VertexType v1,v2;
    int v1_list[11] = {1,1,1,2,3,4,5,5,6,7,8};
    int v2_list[11] = {2,3,4,5,5,6,7,8,8,9,9};
    int w_list[11] = {6,4,5,1,1,2,9,7,4,2,4};
    (*G).vexnum = 9;
    (*G).arcnum = 11;

    //假定该图不含其他信息
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //构造顶点向量
        (*G).vertices[i].data = i+1;
        (*G).vertices[i].firstarc = NULL;
    } //for

    for(k = 0;k<(*G).arcnum;k++){
        v1 = v1_list[k];
        v2 = v2_list[k];
        w = w_list[k];
        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i<0 || j<0)
            return ERROR;

        ArcNode *p;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = (*G).vertices[i].firstarc;
        (*G).vertices[i].firstarc = p;

        p->info = w;
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

Status TopologicalSort(ALGraph G,SqStack *T)
{
    int i,j,count,k;
    int indegree[MAX_VERTEX_NUM];
    ArcNode *p;
    SqStack S;

    FindInDegree(G,indegree);  //对各顶点求入度
    InitStack(&S);
    for(j = 0;j < G.vexnum;j++)
        if(!indegree[j])
        Push(&S,j);

    count = 0;  //对输出顶点计数

    for(i = 0;i<G.vexnum;++i)
        ve[i] = 0;  //初始化

    while(!StackEmpty(S)){
        Pop(&S,&j);
        Push(&(*T),j);
        ++count;
        for(p = G.vertices[j].firstarc; p ;p = p->nextarc){
            k = p->adjvex;   //对i号顶点的每个邻接点的入度-1
            if(!(--indegree[k]))
                Push(&S,k);  //若入度为0，则入栈
            if(ve[j] + p->info > ve[k])
                ve[k] = ve[j]+ p->info;
        }//for
    }//while
    if(count < G.vexnum)
    {
        printf("该有向网有回路\n");
        return ERROR;  //该有向图有回路
    }
    else
        return OK;
}

Status CriticalPath(ALGraph G)
{
    SqStack T;
    int i,j,k,dut,ee,el;
    char tag;
    ArcNode *p;

    InitStack(&T);
    if(!TopologicalSort(G,&T))
        return ERROR;

    j = ve[0];
    for(i = 1;i<G.vexnum;i++)
        if(ve[i] > j)
        j = ve[i];

    for(i = 0;i<G.vexnum;i++)
        vl[i] = j;

    while(!StackEmpty(T))

        for(Pop(&T,&j),p = G.vertices[j].firstarc; p ; p = p ->nextarc){
            k = p->adjvex;
            dut = p->info;
            if(vl[k]-dut  < vl[j])
                vl[j] = vl[k]-dut;
        }//for
    printf("j   k   dut   ee   el   tag\n");

    for(j = 0;j<G.vexnum;j++)
    for(p = G.vertices[j].firstarc; p ;p = p->nextarc){
        k = p->adjvex;
        dut = p->info;
        ee = ve[j];
        el = vl[k]-dut;
        tag = (ee == el) ? '*':' ' ;
        printf("%2d  a%d =%2d  < %2d , %2d>  %2c\n",j,k,dut,ee,el,tag);
    }//for
    printf("输出关键路径：\n");
    for(j = 0;j < G.vexnum; j++){
        for(p = G.vertices[j].firstarc; p ; p = p->nextarc){
            k = p->adjvex;
            dut = p->info;
            if(ve[j] == vl[k]-dut)
                printf("%d->%d\n",G.vertices[j].data,G.vertices[k].data);
        }//for
    }//for
    return OK;
}

/*******************************主函数部分**************************************/
int main()
{
    ALGraph G;
    printf("P168 图7.29\n");
    CreateALGraph_auto(&G);
    CriticalPath(G);
    return 0;
}
