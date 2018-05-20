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

typedef int Status;
typedef int VertexType;
typedef char InfoType;

typedef struct ArcBox
{
    int tailvex,headvex;  //该弧的尾和头顶点的位置
    struct ArcBox *hlink,*tlink;   //分别为弧头相同和弧尾相同的弧的链域
    InfoType *info;  //该弧相关信息的指针
}ArcBox;  //弧结点
typedef struct VexNode
{
    VertexType data;
    ArcBox *firstin,*firstout;  //分别指向该顶点第一条入弧和出弧
}VexNode;  //顶点结点
typedef struct
{
    VexNode xlist[MAX_VERTEX_NUM];  //表头向量 //顺序存储表头结点
    int vexnum,arcnum;  //有向图的当前顶点数和弧数
}OLGraph;  //Othogoal List 十字链表



/*******************************声明部分****************************************/
Status CreateDG(OLGraph *G);
//采用十字链表存储表示，构造有向图G


/*******************************函数部分****************************************/
Status CreateDG(OLGraph *G)
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

    for(i = 0;i<(*G).vexnum;i++){  //构造表头向量
        printf("请输入G.xlist[%d].data = ",i);
        scanf("%d",&(*G).xlist[i].data);  //输入顶点值
        (*G).xlist[i].firstin = NULL;
        (*G).xlist[i].firstout = NULL;  //初始化指针
    }

    for(k = 0;k<(*G).arcnum;k++){  //输入各弧并构造十字链表
        printf("请输入弧头(初始点)：");  //输入一条弧的始点和终点
        scanf("%d",&v1);
        printf("请输入弧尾(终端点)：");
        scanf("%d",&v2);

        i = LocateVex(*G,v1);  //确定v1和v2在G中的位置
        j = LocateVex(*G,v2);

        ArcBox *p;
        p = (ArcBox *)malloc(sizeof(ArcBox));  //假设有足够空间
        p->tailvex = i;  //对弧结点赋值
        p->headvex = j;
        p->hlink = (*G).xlist[j].firstin;
        p->tlink = (*G).xlist[i].firstout;
        p->info = NULL;

        //完成在入弧和出弧链头的插入
        (*G).xlist[j].firstin = (*G).xlist[i].firstout = p;
    }
}

int LocateVex(OLGraph G,VertexType v)
{
    int ct;
    for(ct = 0;ct < G.vexnum;ct++)
        if(G.xlist[ct].data == v)
            return ct;
    return -1;
}


/*******************************主函数部分**************************************/

int main()
{
    printf("构造P465 图7.11 的有向图。\n");
    OLGraph G;
    CreateDG(&G);
}

typedef enum {unvisited, visited} VisitIf;
typedef struct EBox
{
    VisitIf mark;  //访问标记
    int ivex,jvex;  //该边依附的两个顶点的位置
    struct EBox *ilink, *jlink;  //分别指向依附这两个顶点的下一条边
    InfoType *info;
}EBox;
typedef struct VexBox
{
    VertexType data;
    EBox *firstedge;  //指向第一条依附该顶点的边
}VexBox;
typedef struct
{
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexnum,edgenum;  //无向图的当前的顶点数和边数
}AMLGraph;

