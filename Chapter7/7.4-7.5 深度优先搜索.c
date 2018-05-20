#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX 20

#define  INFINITY 65535   //最大值∞
#define MAX_VERTEX_NUM 20  //最大顶点个数

typedef int Status;
typedef int ElemType;
typedef int Boolean;

Boolean Visited[MAX];  //访问标志数组

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
Status CreateUDG(MGraph *G);
//构造无向图  //用以深度优先遍历
int LocateVex(MGraph G,VertexType v);
//确定v在G中的位置
void VisitFunc(MGraph G,int v);
//打印输出第v个顶点的信息
void DFS(MGraph G,int v);
//从第v个顶点出发递归地shenduyouxian图G
void DFSTraverse(MGraph G);
//对图G作深度优先遍历
/*******************************函数部分****************************************/
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

Status CreateUDG_auto(MGraph *G)
{
    printf("\n构造无向图\n");
    int i,j,k; //i,j,k用于计数
    VertexType v1,v2;  //弧头，弧尾
    int v1_list[6] = {1,1,2,3,3,2};
    int v2_list[6] = {2,4,3,4,5,5};

    (*G).vexnum = 5;
    (*G).arcnum = 6;
    //假定该图不含其他信息
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //构造顶点向量
        (*G).vexs[i] = i+1;
    } //for

    for(i = 0;i<(*G).vexnum;i++)  //初始化邻接矩阵
        for(j = 0;j<(*G).vexnum;j++){
            (*G).arcs[i][j].adj = 0;  //无向图
            (*G).arcs[i][j].info = NULL;
        }

    for(k = 0;k<(*G).arcnum;k++){  //构造邻接矩阵
        v1 = v1_list[k];
        v2 = v2_list[k];
        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = (*G).arcs[j][i].adj = 1;
            //置<v1,v2>的对称弧<v2,v1>
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



void DFS(MGraph G,int v)
{
    int w;
    Visited[v] = TRUE;
    printf("%d ",G.vexs[v]);  //打印该顶点
    for(w = 0;w<G.vexnum;w++)
        if(G.arcs[v][w].adj == 1 && !Visited[w])
            DFS(G,w);  //对v的尚未访问的邻接顶点w递归调用DFS
}

void DFSTraverse(MGraph G)
{
    printf("\nDFS遍历该图.\n");
    int v;
    for(v = 0;v<G.vexnum;++v)  //访问标志数组初始化
        Visited[v] = FALSE;
    for(v = 0;v<G.vexnum;++v)
        if(!Visited[v])
            DFS(G,v);  //对尚未访问的顶点调用DFS
}

/*******************************主函数部分**************************************/
int main()
{
    MGraph G;
    printf("自动创建无向图(P157,G2)：\n");
    CreateUDG_auto(&G);
    DFSTraverse(G);
    return 0;
}
