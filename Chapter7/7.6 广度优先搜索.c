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
typedef int QElemType;

#define MAXQSIZE 100  //max queue length
typedef struct
{
    QElemType *base;  //初始化的动态分配存储空间
    int front;  //head pointer,若队列不空，指向队列头元素
    int rear;  //tail pointer,若队列不空，指向队列尾元素的下一个位置
}SqQueue;

#define INFINITY 65535   //最大值∞
#define MAX_VERTEX_NUM 20  //最大顶点个数
#define MAX 20
typedef int Status;
typedef int ElemType;
typedef int Boolean;

Boolean visited[MAX];  //访问标志数组

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



/*******************************函数部分****************************************/
Status InitQueue(SqQueue *Q)
{
    Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if(!Q->base)
        exit(OVERFLOW);
    Q->front = Q->rear = 0;
    return OK;
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

Status QueueEmpty(SqQueue Q)
{
    return (Q.front == Q.rear);
}

int FirstAdjVex(MGraph G,int v)
{
    int k,j;
    v = LocateVex(G,v);
    if(v > 0){
    for(j = 0;j <G.vexnum;j++)
        if(G.arcs[v][j].adj != 0){
            return j;
        }
    }
    return -1;
}

int NextAdjVex(MGraph G,int v,int w)
{
    int j;
    v = LocateVex(G,v);
    if(v>0){
    for(j = w+1;j<G.vexnum;j++)
        if(G.arcs[v][j].adj != 0){
            return j;
        }
    }
    return -1;
}

int LocateVex(MGraph G,VertexType v)
{
    int ct;
    for(ct = 0;ct < G.vexnum;ct++)
        if(G.vexs[ct] == v)
            return ct;
    return -1;
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
    for(i = 0;i<(*G).vexnum;i++){  //初始化顶点向量
       (*G).vexs[i]=0;
    } //for

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
    G->kind = UDG;
    return OK;
}

Status CreateUDG_auto(MGraph *G)
{
    printf("\n构造无向图\n");
    int i,j,k; //i,j,k用于计数
    VertexType v1,v2;  //弧头，弧尾

    G->vexnum = 8;
    G->arcnum = 9;
    //假定该图不含其他信息
    int IncInfo = 0;

    for(i = 0;i<(*G).vexnum;i++){  //构造顶点向量
        G->vexs[i] = i+1;
    } //for

    for(i = 0;i<(*G).vexnum;i++)  //初始化邻接矩阵
        for(j = 0;j<(*G).vexnum;j++){
            (*G).arcs[i][j].adj = 0;  //无向图
            (*G).arcs[i][j].info = NULL;
        }

    int v1_list[9] = {1,1,2,2,3,3,4,5,6};
    int v2_list[9] = {2,3,4,5,6,7,8,8,7};
    for(k = 0;k<(*G).arcnum;k++){  //构造邻接矩阵
        v1 = v1_list[k];
        v2 = v2_list[k];

        i = LocateVex(*G,v1);
        j = LocateVex(*G,v2);

        if(i>=0 && j>=0)
            (*G).arcs[i][j].adj = (*G).arcs[j][i].adj = 1;
            //置<v1,v2>的对称弧<v2,v1>
    }
    G->kind = UDG;
    return OK;
}

void BFSTraverse(MGraph G)
{
    SqQueue Q;
    int v,u,w , visited[G.vexnum],ct;
    for(v = 0;v<G.vexnum;++v)
        visited[v] = FALSE;
    InitQueue(&Q);

    for(v = 0;v<G.vexnum;++v)
    if(!visited[v]){
        visited[v] = TRUE;
        printf("%d ",G.vexs[v]);
        EnQueue(&Q,v);
        while(!QueueEmpty(Q)){
            DeQueue(&Q,&u);
            for(w = FirstAdjVex(G,u);w>=0;w = NextAdjVex(G,u,w))
            if(w>0&&!visited[w]){
                visited[w] = TRUE;
                printf("%d ",G.vexs[w]);
                EnQueue(&Q,w);
            }//if
        }//while
    }//if
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
    CreateUDG_auto(&G);

    printf("\nBFS遍历输出：\n");

    BFSTraverse(G);
    return 0;
}



