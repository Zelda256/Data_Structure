#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define  INFINITY 65535   //最大值∞
#define MAX_VERTEX_NUM 20  //最大顶点个数

typedef int Status;
typedef int VRType;
typedef char InfoType;
typedef int VertexType;
typedef enum {DG,DN,UDG,UDN}GraphKind;   //{有向图，有向网，无向图，无向网}

typedef struct ArcCell
{
    VRType adj;  //VRType 是顶点关系类型。对无权图，用0或1表示相邻否；对带权图，则为权值类型
    InfoType *info; //该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];  //顶点向量
    AdjMatrix arcs;  //邻接矩阵
    int vexnum,arcnum;  //图的当前顶点数和弧数
    GraphKind kind;  //图的种类标志
}MGraph;

/*******************************声明部分****************************************/
Status CreateGraph (MGraph *G);
//采用数组（邻接矩阵）表示法，构造图G
Status CreateDG(MGraph *G);
 //构造有向图
Status CreateDN(MGraph *G);
//构造有向网
Status CreateUDG(MGraph *G);
//构造无向图
Status CreateUDN(MGraph *G);
//构造无向网
int LocateVex(MGraph G,VertexType v);
//确定v在G中的位置
Status PrintfArcs(MGraph G);
//输出图G的邻接矩阵
/*******************************函数部分****************************************/
Status CreateGraph (MGraph *G)
{
    printf("请输入图的类型：\n");
    printf("0:有向图  1:有向网  2:无向图  3:无向网\n");
    scanf("%d",&(*G).kind);
    switch((*G).kind)
    {
        case DG: return CreateDG(G);  //构造有向图
        case DN: return CreateDN(G);  //构造有向网
        case UDG: return CreateUDG(G);  //构造无向图
        case UDN: return CreateUDN(G);  //构造无向网
        default : return ERROR;
    }
}
Status CreateDG(MGraph *G)
{
    printf("\n构造有向图\n");
    int i,j,k; //i,j,k用于计数
    VertexType v1,v2;  //弧头，弧尾

    printf("请输入顶点个数：");
    scanf("%d",&(*G).vexnum);
    printf("请输入弧个数：");
    scanf("%d",&(*G).arcnum);
    //假定该图不含其他信息
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //构造顶点向量
        printf("请输入G.vexs[%d] = ",i);
        scanf("%d",&(*G).vexs[i]);
    } //for

    for(i = 0;i<(*G).vexnum;i++)  //初始化邻接矩阵
        for(j = 0;j<(*G).vexnum;j++){
            (*G).arcs[i][j].adj = 0;  //无向图
            (*G).arcs[i][j].info = NULL;
        }

    for(k = 0;k<(*G).arcnum;k++){  //构造邻接矩阵
        printf("请输入弧头(初始点)：");  //输入一条弧的始点和终点
        scanf("%d",&v1);
        printf("请输入弧尾(终端点)：");
        scanf("%d",&v2);

        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = 1;
    }
    return OK;
}
Status CreateDN(MGraph *G)
{
    printf("\n构造有向网\n");
    int i,j,k; //i,j,k用于计数
    int w;  //权重
    VertexType v1,v2;  //弧头，弧尾

    printf("请输入顶点个数：");
    scanf("%d",&(*G).vexnum);
    printf("请输入弧个数：");
    scanf("%d",&(*G).arcnum);
    //假定该图不含其他信息
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //构造顶点向量
        printf("请输入G.vexs[%d] = ",i);
        scanf("%d",&(*G).vexs[i]);
    } //for

    for(i = 0;i<(*G).vexnum;i++)  //初始化邻接矩阵
        for(j = 0;j<(*G).vexnum;j++){
            (*G).arcs[i][j].adj = INFINITY;  //无向网
            (*G).arcs[i][j].info = NULL;
        }

    for(k = 0;k<(*G).arcnum;k++){  //构造邻接矩阵
        printf("请输入弧头(初始点)：");  //输入一条弧的始点和终点
        scanf("%d",&v1);
        printf("请输入弧尾(终端点)：");
        scanf("%d",&v2);
        printf("请输入权重：");
        scanf("%d",&w);

        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = w;  //置<v1,v2>的对称弧<v2,v1>

        //不再输入该弧含有的相关信息
    }
    return OK;
}
Status CreateUDG(MGraph *G)
{
    printf("\n构造无向图\n");
    int i,j,k; //i,j,k用于计数
    VertexType v1,v2;  //弧头，弧尾

    printf("请输入顶点个数：");
    scanf("%d",&(*G).vexnum);
    printf("请输入弧个数：");
    scanf("%d",&(*G).arcnum);
    //假定该图不含其他信息
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //构造顶点向量
        printf("请输入G.vexs[%d] = ",i);
        scanf("%d",&(*G).vexs[i]);
    } //for

    for(i = 0;i<(*G).vexnum;i++)  //初始化邻接矩阵
        for(j = 0;j<(*G).vexnum;j++){
            (*G).arcs[i][j].adj = 0;  //无向图
            (*G).arcs[i][j].info = NULL;
        }

    for(k = 0;k<(*G).arcnum;k++){  //构造邻接矩阵
        printf("请输入弧头(初始点)：");  //输入一条弧的始点和终点
        scanf("%d",&v1);
        printf("请输入弧尾(终端点)：");
        scanf("%d",&v2);

        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = (*G).arcs[j][i].adj = 1;
            //置<v1,v2>的对称弧<v2,v1>
    }
    return OK;
}
Status CreateUDN(MGraph *G)
{
    printf("\n3构造无向网\n");
    int i,j,k; //i,j,k用于计数
    int w;  //权重
    VertexType v1,v2;  //弧头，弧尾

    printf("请输入顶点个数：");
    scanf("%d",&(*G).vexnum);
    printf("请输入弧个数：");
    scanf("%d",&(*G).arcnum);
    //假定该图不含其他信息
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //构造顶点向量
        printf("请输入G.vexs[%d] = ",i);
        scanf("%d",&(*G).vexs[i]);
    } //for

    for(i = 0;i<(*G).vexnum;i++)  //初始化邻接矩阵
        for(j = 0;j<(*G).vexnum;j++){
            (*G).arcs[i][j].adj = INFINITY;  //无向网
            (*G).arcs[i][j].info = NULL;
        }

    for(k = 0;k<(*G).arcnum;k++){  //构造邻接矩阵
        printf("请输入弧头(初始点)：");  //输入一条弧的始点和终点
        scanf("%d",&v1);
        printf("请输入弧尾(终端点)：");
        scanf("%d",&v2);
        printf("请输入权重：");
        scanf("%d",&w);

        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = (*G).arcs[j][i].adj = w;  //置<v1,v2>的对称弧<v2,v1>

        //不再输入该弧含有的相关信息
    }
    return OK;
}
int LocateVex(MGraph G,VertexType v)
{
    int ct;
    for(ct = 0;ct < G.vexnum;ct++)
        if(G.vexs[ct] == v)
            return ct;
    return -1;
}
Status PrintfArcs(MGraph G)
{
    int n = G.vexnum;
    int i,j;  //i,j用于计数
    for(i = 0;i < n;i++){
        for(j = 0;j<n;j++){
            if(G.arcs[i][j].adj == INFINITY)
                printf("∞ ");
            else
                printf("%d ",G.arcs[i][j].adj);
        }
        printf("\n");
    }
    return OK;
}
/*******************************主函数部分**************************************/

int main()
{
    MGraph G;
    CreateGraph(&G);
    PrintfArcs(G);
    return 0;
}

typedef struct ArcNode
{
    int adjvex;  //该弧所指向的顶点的位置
    struct ArcNode *nextarc;  //指向下一条弧的指针
    InfoType *info;  //该弧相关信息的指针
}ArcNode;  //表结点
typedef struct VNode
{
    VertexType data;   //顶点信息
    ArcNode *firstarc;  //指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];  //头结点
typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;  //图的当前顶点数和弧数
    int kind;
}ALGraph;
