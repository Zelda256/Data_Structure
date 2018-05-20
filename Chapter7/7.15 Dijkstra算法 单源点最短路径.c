#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20  //最大顶点个数
#define  INFINITY 65535   //最大值∞

typedef int Status;
typedef enum {DG,DN,UDG,UDN} GraphKind;   //{有向图，有向网，无向图，无向网}

typedef struct
{
    int vexs[MAX_VERTEX_NUM];  //顶点向量
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //邻接矩阵
    int vexnum,arcnum;  //图的当前顶点数和弧数
    GraphKind kind;  //图的种类标志
}MGraph;

typedef int PathMatrix;
typedef int ShortPathTable;

/*******************************声明部分****************************************/
Status CreateDN(MGraph *G);
//构造有向网
int LocateVex(MGraph G,int v);
//确定v在G中的位置
Status ShortestPath_DIJ(MGraph G,int v0,PathMatrix *p,ShortPathTable *D);
//用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及其带权长度D[v]

/*******************************函数部分****************************************/
Status CreateDN(MGraph *G)
{
    printf("\n构造有向网\n");
    int i,j,k; //i,j,k用于计数
    int w;  //权重
    int v1,v2;  //弧头，弧尾

 /*   printf("请输入顶点个数：");
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
        for(j = 0;j<(*G).vexnum;j++)
            (*G).arcs[i][j] = INFINITY;  //有向网

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
            (*G).arcs[i][j] = w;  //置<v1,v2>的对称弧<v2,v1>
    */
    (*G).vexnum = 6;
    (*G).arcnum = 8;
    for(i = 0;i<(*G).vexnum;i++)
        (*G).vexs[i] = i;
    for(i = 0;i<(*G).vexnum;i++)
        for(j = 0;j<(*G).vexnum;j++)
            (*G).arcs[i][j] = INFINITY;

    (*G).arcs[0][2] = 10;
    (*G).arcs[1][2] = 5;
    (*G).arcs[2][3] = 50;
    (*G).arcs[4][3] = 20;
    (*G).arcs[0][4] = 30;
    (*G).arcs[0][5] = 100;
    (*G).arcs[3][5] = 10;
    (*G).arcs[4][5] = 60;

    return OK;
}

int LocateVex(MGraph G,int v)
{
    int ct;
    for(ct = 0;ct < G.vexnum;ct++)
        if(G.vexs[ct] == v)
            return ct;
    return -1;
}

Status ShortestPath_DIJ(MGraph G,int v0,PathMatrix *p,ShortPathTable *D)
{
    int v,w,i,min,j;
    int final[MAX_VERTEX_NUM];
    for(v = 0;v<G.vexnum;v++){
        final[v] = 0;
        D[v] = G.arcs[v0][v];
        p[v] = -1;
    }//for
    D[v0] = 0;
    final[v0] = 1;  //初始化，v0顶点属于S集
    //开始主循环，每次求得v0到某个v顶点的最短路径，并加v到S集
    for(i = 0;i<G.vexnum;++i){   //其余G.vexnum-1个顶点
        min =INFINITY;     //当前所知离v0顶点的最近距离
        for(w = 0;w < G.vexnum;++w)
            if(!final[w])
                if(D[w]<min){   //w顶点在V-S中
                    v = w;
                    min = D[w];   //w顶点离v0顶点更近
                }//if
        final[v] = 1;  //离v0顶点最近的v加入S集
        for(w = 0;w<G.vexnum;w++)   //更新当前最短路径及距离
            if(!final[w] && (min+G.arcs[v][w]<D[w])){  //修改D[w]和P[w],w属于V-S
                D[w] = min+G.arcs[v][w];
                for(j = 1;j<G.vexnum;j++)
                    p[w] = v;
            }//if
    }//for
}
/*******************************主函数部分**************************************/

int main()
{
    MGraph G;
    ShortPathTable D[MAX_VERTEX_NUM];
    PathMatrix P[MAX_VERTEX_NUM];
    int v0 = 0,i,j;
    CreateDN(&G);
    ShortestPath_DIJ(G,v0,P,D);
    printf("\n最短路径倒叙如下：\n");
    for(i = 0;i<G.vexnum;i++){
        printf("v%d - v%d : ",v0,i);
        j = i;
        printf("v%d",i);
        while(P[j] != -1){
            printf("<-");
            printf("v%d",P[j]);
            j = P[j];
        }
        printf("<-v0");
        printf("\n");
    }
    printf("\n源点到各顶点的最短路径长度为：\n");
    for(i = 0;i<G.vexnum;i++){
        if(D[i] != INFINITY)
            printf("v%d-v%d : %d \n",G.vexs[0],G.vexs[i],D[i]);
        else
            printf("v%d-v%d : ∞ \n",G.vexs[0],G.vexs[i]);
    }
    return 0;
}
