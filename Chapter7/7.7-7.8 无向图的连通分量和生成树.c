#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAXSIZE 20  //最大顶点数
typedef int Status;
typedef int ElemType;
typedef struct CSNode
{
    ElemType data;
    struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

typedef int Boolean;
Boolean Visited[MAXSIZE];  //访问标志数组

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
int FirstAdjVex(MGraph G,int v);
//返回v的第一个邻接顶点
int NextAdjVex(MGraph G,int v,int w);
//返回v的（相对于w的）下一个邻接顶点
VertexType Getvex(MGraph G,int v);
//v是G中的某个顶点，返回v的值

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
    G->kind = UDG;
    return OK;
}

Status CreateUDG_auto(MGraph *G)
{
    printf("\n构造无向图\n");
    int i,j,k; //i,j,k用于计数
    VertexType v1,v2;  //弧头，弧尾

    G->vexnum = 5;
    G->arcnum = 6;
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

    int v1_list[6] = {1,1,2,3,3,2};
    int v2_list[6] = {2,4,3,4,5,5};
    for(k = 0;k<(*G).arcnum;k++){  //构造邻接矩阵

        scanf("%d",&v2);*/
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
            printf("%d ",G.arcs[i][j]);
        }
        printf("\n");
    }
    return OK;
}

VertexType Getvex(MGraph G,int v)
{
    return G.vexs[v];
}

int FirstAdjVex(MGraph G,int v)
{

    int k,j ,t;
    k = LocateVex(G,v);
    if(k)
    {
        t = 0;
        for(j = 0;j <G.vexnum;j++)
            if(G.arcs[k][j].adj != t)
                return j;
    }
    return -1;
}

int NextAdjVex(MGraph G,int v,int w)
{
    int j,t,k1,k2;
    t = 0;
    for(j = w+1;j<G.vexnum;j++)
        if(G.arcs[v][j].adj != t)
            return j;
    return -1;
}

void DFSTree(MGraph G,int v,CSTree *T)
{
    int first,w;
    CSTree p,q;
    Visited[v] = TRUE;
    first = TRUE;

    for(w = FirstAdjVex(G,G.vexs[v]);w >= 0;w = NextAdjVex(G,G.vexs[v],G.vexs[w])){
        if(!Visited[w]){
            p = (CSTree)malloc(sizeof(CSNode));  //分配孩子结点
            p->data = Getvex(G,w);   //给该结点赋值
            p->firstchild = NULL;
            p->nextsibling = NULL;
            if(first){      //w是v的第一个未被访问的邻接顶点
                (*T)->firstchild = p;  //是根的左孩子结点
                first = FALSE;
            }//if
            else  //w是v的其他未被访问的邻接顶点
                q->nextsibling = p;  //是上一邻接顶点的右兄弟结点
            q = p;
            DFSTree(G,w,&q);  //从第w个顶点出发深度优先遍历图G，建立子生成树q
        }//if
    }//for
}

void DFSForest(MGraph G,CSTree *T)
{
    int v;
    CSTree p,q;

    *T = p = q = NULL;
    for(v = 0;v<G.vexnum;v++)
        Visited[v] = FALSE;

    for(v = 0;v<G.vexnum;v++)
    if(!Visited[v]){    //第v顶点为新的生成树的根的根结点
        p = (CSTree)malloc(sizeof(CSNode));  //分配根结点
        p->data = Getvex(G,v);   //给该结点赋值
        p->firstchild = NULL;
        p->nextsibling = NULL;
        if(!(*T))
            *T = p;  //是第一棵生成树的根（T的根）
        else
            q->nextsibling = p;  //是其他生成树的根（前一棵树的根的“兄弟”）
        q = p;  //q指示当前生成树的根
        DFSTree(G,v,&p);  //建立以p为根的生成树
    }//if
}

Status Visit(int e)
{
    printf("%d,",e);
    return OK;
}

Status PreOrderTraverse(CSTree T,Status(*Visit)(int e))  //递归
{
    if(T){
        if(Visit(T->data))
            if(PreOrderTraverse(T->firstchild,Visit))
                if(PreOrderTraverse(T->nextsibling,Visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

void VisitFunc(MGraph G,int v)
{
    printf("%d ",G.vexs[v]);  //打印该顶点
}

void DFS(MGraph G,int v)
{
    int w;
    Visited[v] = TRUE;
    VisitFunc(G,v);  //访问第v个顶点
    for(w = 0;w<G.vexnum;w++)
        if(G.arcs[v][w].adj == 1 && !Visited[w])
            DFS(G,w);  //对v的尚未访问的邻接顶点w递归调用DFS
}

void DFSTraverse(MGraph G)
{
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
    printf("\n创建并输出无向图（数组表示法）：\n");
    CreateUDG_auto(&G);
    PrintfArcs(G);
    printf("\n创建完毕,DFS遍历输出图:\n");
    DFSTraverse(G);

    CSTree T;
    printf("\n\n创建并输出无向图的生成树：\n");
    DFSForest(G,&T);
    printf("\n创建完毕,输出树\n");
    PreOrderTraverse(T,Visit);
    return 0;
}




