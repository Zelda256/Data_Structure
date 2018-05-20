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

typedef struct
{
    VertexType adjvex;
    VRType lowcost;
}CLOSEDGE;

/*******************************声明部分****************************************/
Status CreateUDN(MGraph *G);
//构造无向网
int LocateVex(MGraph G,VertexType v);
//确定v在G中的位置
int minimum(CLOSEDGE closedge[],int n);
//返回最小连接的顶点序号
void MiniSpanTree_PRIM(MGraph G,VertexType u);
//用普里姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边
//记录从顶点集U到V-U的代价最小的边的辅助数组定义
/*******************************函数部分****************************************/
Status CreateUDN(MGraph *G)
{
    printf("\n构造无向网\n");
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
    (*G).kind = UDN;
    return OK;
}

Status CreateUDN_auto(MGraph *G)
{
    printf("\n构造无向网\n");
    int i,j,k; //i,j,k用于计数
    int w;  //权重
    VertexType v1,v2;  //弧头，弧尾
    int v1_list[10] = {1,1,2,2,3,3,3,5,4,1};
    int v2_list[10] = {2,3,3,5,5,6,4,6,6,4};
    int w_list[10] = {6,1,5,3,6,4,5,6,2,5};


    (*G).vexnum = 6;
    (*G).arcnum = 10;
    //假定该图不含其他信息
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //构造顶点向量
        (*G).vexs[i] = i+1;
    } //for

    for(i = 0;i<(*G).vexnum;i++)  //初始化邻接矩阵
        for(j = 0;j<(*G).vexnum;j++){
            (*G).arcs[i][j].adj = INFINITY;  //无向网
            (*G).arcs[i][j].info = NULL;
        }

    for(k = 0;k<(*G).arcnum;k++){  //构造邻接矩阵
        v1 = v1_list[k];
        v2 = v2_list[k];
        w = w_list[k];

        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = (*G).arcs[j][i].adj = w;  //置<v1,v2>的对称弧<v2,v1>

        //不再输入该弧含有的相关信息
    }
    (*G).kind = UDN;
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

int minimum(CLOSEDGE closedge[],int n)
{
    int i = 0,j,min,k;
    while(!closedge[i].lowcost)
        i++;
    min = closedge[i].lowcost;
    k = i;
    for(j = 1;j<n;j++)
        if( closedge[j].lowcost)
            if(min > closedge[j].lowcost) {
                min = closedge[j].lowcost;
                k = j;
            }//if
    return k;
}

void MiniSpanTree_PRIM(MGraph G,VertexType u)
{
    CLOSEDGE closedge[G.vexnum+1];
    int k,j,i;

    k = LocateVex(G,u);
    for(j = 0;j<G.vexnum;++j)
        if(j!=k){  //辅助数组初始化
            closedge[j].adjvex = u;
            closedge[j].lowcost = G.arcs[k][j].adj;
        }//if

    closedge[k].lowcost = 0;  //初始，U = {u}
    for(i = 1;i<G.vexnum ;++i){  //选择其余G.vexnum-1个顶点

        k = minimum(closedge,G.vexnum);  //求出T的下一个结点：第k个顶点
        printf("(%d,%d)\n",closedge[k].adjvex,G.vexs[k]);  //输出生成树的边

        closedge[k].lowcost = 0;  //第k顶点并入U集

        for(j = 0;j<G.vexnum;++j){
        if(G.arcs[k][j].adj < closedge[j].lowcost){  //新顶点并入U集后重新选择最小边
            closedge[j].adjvex = G.vexs[k];
            closedge[j].lowcost = G.arcs[k][j].adj;
        }//if
        }//for
    }//for
}

/*******************************主函数部分**************************************/

int main()
{
    MGraph G;
    printf("P174 图7.16（a）\n");
    CreateUDN_auto(&G);
    printf("\n输出生成树上的5条边为：\n");
    MiniSpanTree_PRIM(G,1);
    return 0;
}
