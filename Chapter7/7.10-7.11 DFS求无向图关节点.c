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

int count;  //全局变量count对访问计数。
int Visited[MAX_VERTEX_NUM];
int low[MAX_VERTEX_NUM];
/*******************************声明部分****************************************/
Status CreateALGraph(ALGraph *G);
//创建邻接表方式存储的无向图
int LocateVex(ALGraph G,VertexType v);
//确定v在G中的位置
void DFSArticul(ALGraph G,int v0);
//从第v0个顶点出发深度优先遍历图G，查找并输出关节点
void FindArticul(ALGraph G);
//连通图G以邻接表作存储结构，查找并输出G上全部关节点
/*******************************函数部分****************************************/
Status CreateALGraph(ALGraph *G)
{
    printf("开始创建无向图\n");
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
        ArcNode *p,*q;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = NULL;

        if(r[i] == NULL)    //邻接表中第一个结点
            (*G).vertices[i].firstarc = p;   //加入到邻接表
        else
            r[i]->nextarc = p;
        r[i] = p;

        q = (ArcNode *)malloc(sizeof(ArcNode));
        q->adjvex = i;
        q->nextarc = NULL;

        if(r[j] == NULL)    //邻接表中第一个结点
            (*G).vertices[j].firstarc = q;   //加入到邻接表
        else
            r[j]->nextarc = q;
        r[j] = q;
    }
    return OK;
}

Status CreateALGraph_auto(ALGraph *G)
{
    printf("开始创建无向图\n");
    int i,j,k;
    VertexType v1,v2;
    ArcNode *r[MAX_VERTEX_NUM+1];
    int v1_list[17] = {1,1,1,1,12,10,10,2,2,2,2,2,8,7,11,7,4};
    int v2_list[17] = {12,2,3,6,13,12,13,13,8,7,4,3,11,8,7,9,5};

    (*G).vexnum = 13;
    (*G).arcnum = 17;
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
        ArcNode *p,*q;
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextarc = NULL;

        if(r[i] == NULL)    //邻接表中第一个结点
            (*G).vertices[i].firstarc = p;   //加入到邻接表
        else
            r[i]->nextarc = p;
        r[i] = p;

        q = (ArcNode *)malloc(sizeof(ArcNode));
        q->adjvex = i;
        q->nextarc = NULL;

        if(r[j] == NULL)    //邻接表中第一个结点
            (*G).vertices[j].firstarc = q;   //加入到邻接表
        else
            r[j]->nextarc = q;
        r[j] = q;
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

void DFSArticul(ALGraph G,int v0)
{
    int min,w;
    ArcNode *p;

    Visited[v0] = min = ++count;  //v0是第count个访问的顶点
    for(p = G.vertices[v0].firstarc; p ;p = p->nextarc){  //对v0的每个邻接顶点检查
        w = p->adjvex;  //w为v0的邻接顶点
        if(Visited[w] == 0){  //w未曾访问，是v0的孩子
            DFSArticul(G,w);  //返回前求得low[w]
            if(low[w] < min)
                min = low[w];
            if(low[w] >= Visited[v0])
                printf("%d,%d\n",v0,G.vertices[v0].data);  //关节点
        }//if
        else if(Visited[w] < min)
            min = Visited[w];  //w已访问，w是v0在生成树上的祖先
    }//for
    low[v0] = min;
}

void FindArticul(ALGraph G)
{
    int i,v;
    ArcNode *p;

    count = 1;
    low[0] = Visited[0] = 1;  //设定邻接表上0号顶点为生成树的根

    for(i = 1;i<G.vexnum;++i)
        Visited[i] = 0;  //其余顶点尚未访问

    p = G.vertices[0].firstarc;
    v = p->adjvex;

    DFSArticul(G,v);  //从第v顶点出发深度优先查找关节点

    if(count < G.vexnum){
        printf("%d,%d\n",0,G.vertices[0].data);
        while(p->nextarc){
            p = p->nextarc;
            v = p->adjvex;
            if(Visited[v] == 0)
                DFSArticul(G,v);
        }//while
    }//if
}

/*******************************主函数部分**************************************/

int main()
{
    int i;
    ALGraph G;

    printf("P177,图7.19 G5\n");
    CreateALGraph_auto(&G);

    printf("\n关节点及关节点保存的的值为：\n");
    FindArticul(G);
    return 0;
}


