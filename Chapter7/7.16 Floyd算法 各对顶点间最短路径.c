#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX 20  //最大顶点个数
#define  INFINITY 65535   //最大值∞

typedef int Status;
typedef enum {DG,DN,UDG,UDN} GraphKind;   //{有向图，有向网，无向图，无向网}

typedef struct
{
    int vexs[MAX];  //顶点向量
    int arcs[MAX][MAX];  //邻接矩阵
    int vexnum,arcnum;  //图的当前顶点数和弧数
    GraphKind kind;  //图的种类标志
}MGraph;

typedef int PathMatrix[MAX][MAX][MAX];
typedef int DistanceMatrix[MAX][MAX];

/*******************************声明部分****************************************/
Status CreateDN(MGraph *G);
//构造有向网
int LocateVex(MGraph G,int v);
//确定v在G中的位置
void ShortestPath_FLOYD(MGraph G,PathMatrix *P,DistanceMatrix *D);
//用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w]及其
//带权长度D[v][w].若P[v][w]为TRUE，则u是从v到w当前求得最短路径上的顶点
/*******************************函数部分****************************************/
Status CreateDN(MGraph *G)
{
    printf("\n构造有向网\n");
    int i,j,k; //i,j,k用于计数
    int w;  //权重
    int v1,v2;  //弧头，弧尾

  /*  printf("请输入顶点个数：");
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
            (*G).arcs[i][j] = w;
        }*/

    (*G).vexnum = 3;
    (*G).arcnum = 5;

    for(i = 0;i<(*G).vexnum;i++)
        (*G).vexs[i] = i;

    for(i = 0;i<(*G).vexnum;i++)
        for(j = 0;j<(*G).vexnum;j++)
            (*G).arcs[i][j] = INFINITY;

    (*G).arcs[0][1] = 4;
    (*G).arcs[0][2] = 11;
    (*G).arcs[1][0] = 6;
    (*G).arcs[1][2] = 2;
    (*G).arcs[2][0] = 3;

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

void ShortestPath_FLOYD(MGraph G,PathMatrix *P,DistanceMatrix *D)
{
    int v,w,u,i;

    for(v = 0;v<G.vexnum;v++)    //各顶点之间初始已知路径及距离

        for(w = 0;w<G.vexnum;w++){

            (*D)[v][w] = G.arcs[v][w];

            for(u = 0;u<G.vexnum;u++)
                (*P)[v][w][u] = 0;

            if((*D)[v][w] < INFINITY){   //从v到w有直接路径
                (*P)[v][w][v] = 1;
                (*P)[v][w][w] = 1;
            }//if
        }//for
    for(u = 0;u<G.vexnum;u++)
        for(v = 0;v<G.vexnum;v++)
            for(w = 0;w<G.vexnum;w++)
                if((*D)[v][u] + (*D)[u][w] < (*D)[v][w]){   //从v经过u到w的一条路径更短
                    (*D)[v][w] = (*D)[v][u] + (*D)[u][w];

                    for(i = 0;i<G.vexnum;i++)
                        (*P)[v][w][i] = (*P)[v][u][i] || (*P)[u][w][i];
                }//if

}

/*******************************主函数部分**************************************/
int main()
{
    int v,w,k;
    MGraph G;
    PathMatrix P;
    DistanceMatrix D;

    CreateDN(&G);
    ShortestPath_FLOYD(G,&P,&D);

    printf("\n各顶点间最短路径如下：\n");
    for(v = 0;v<G.vexnum;v++)
        for(w = 0;w<G.vexnum;w++){
            if(v!=w){
                printf("\nv%d-v%d : 权重: %2d , ",G.vexs[v],G.vexs[w],D[v][w]);
                printf("路径：v%d",v);
                for(k = 0;k<G.vexnum;k++)
                //    if(k!=w )
                        printf("->v%d",P[v][w][k]);
            }
            printf("->v%d",w);
        }
}
