#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW_SELF -2

#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) <  (b))
#define LQ(a,b) ((a) <= (b))
#define M 3
typedef int Status;
typedef int ElemType;
typedef int KeyType;
typedef struct
{
    ElemType *elem; //unit elem[0] keep NULL
    int length;   //length of table
}SSTable;
typedef struct BTNode
{
    int keynum;   //结点中关键字个数，即结点的大小
    struct BTNode *parent;  //point to Parent node
    KeyType key[M+1];    //关键字向量，0号单元未用
    struct BTNode *ptr[M+1];  //子树指针向量
}BTNode,*BTree;
typedef struct
{
    BTNode *pt;  //指向找到的结点
    int i;   //1...M，在结点中的关键字序号
    int tag;  //1:found,0:unfound
}Result;  //B-Tree 的查找结果类型
/*******************************声明部分****************************************/
int Search(BTree p,KeyType K);
//在p->key[1...keynum]中查找，返回值i使得：p->key[i] <= K < p->key[i+1]
Result SearchBTree(BTree T,KeyType K);
//在M阶B树T上查找关键字K，返回结果（pt,i,tag),若查找成功，则特征值tag = 1，
//指针pt所指结点中第i个关键字等于K，否则特征值tag = 0，等于K的关键字应插入
//在指针pt所指结点中第i个和第i+1个关键字之间
Status insert(BTree q,int i,KeyType x,BTree ap);
//将x和ap分别插入到q->key[i+1]和q->ptr[i+1]
Status split(BTree q,int s,BTree *ap);
//将q->key[s+1...M],q->ptr[s...M]和q->recptr[s+1...M]移入新结点*ap
Status NewRoot(BTree *T,BTree q,KeyType x,BTree ap);
//生成含信息(T,x,ap)的新的根结点*T，原T和ap为子树指针
Status InsertBTree(BTree *T,KeyType K,BTree q,int i);
//在M阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K，
//若引起结点过大，则沿双亲链进行必要的结点分裂调整，使T仍是M阶B树
Status CreateTalbe(SSTable *L);
Status InitTable(SSTable *L);

/*******************************函数部分****************************************/
int Search(BTree p,KeyType K)
{
    int i,j;
    for(i = 0,j = 1;j <= p->keynum;j++){
        if(p->key[j] <= K)
            i = j;
        else
            break;
    }
    return i;
}

Result SearchBTree(BTree T,KeyType K)
{
    BTree p,q;
    int found,i;

    p = T;  //初始化，p指向待查结点，q指向p的双亲
    q = NULL;
    found = FALSE;
    i = 0;

    while(p && !found){
        i = Search(p,K);
        if(i > 0 && p->key[i] == K)
            found = TRUE;  //找到关键字
        else{
            q = p;
            p = p->ptr[i];
        }
    }//while
    if(found){
        Result R1;
        R1.pt = p;
        R1.i = i;
        R1.tag = 1;
        return R1;
    }
    else{
        Result R0;
        R0.pt = q;
        R0.i = i;
        R0.tag = 0;
        return R0;
    }
}

Status Insert(BTree q,int i,KeyType x,BTree ap)
{
    int j;

    for(j = q->keynum;j > i;j--){   //所有元素后移
        q->key[j+1] = q->key[j];
        q->ptr[j+1] = q->ptr[j];
    }

    q->key[i+1] = x;
    q->ptr[i+1] = ap;
    q->keynum++;
    return OK;
}

Status split(BTree q,int s,BTree *ap)
{
    int i;

    (*ap) = (BTree)malloc(sizeof(BTNode));
    (*ap)->ptr[0] = q->ptr[s];

    for(i = s+1; i <= M;i++){
        (*ap)->key[i-s] = q->key[i];
        (*ap)->ptr[i-s] = q->ptr[i];
    }

    (*ap)->keynum = M - s;
    q->keynum = s-1;
    (*ap)->parent = q->parent;

    for(i = 0;i<=(*ap)->keynum;i++){
        if((*ap)->ptr[i])
            (*ap)->ptr[i]->parent = *ap;
    }
}

Status NewRoot(BTree *T,BTree q,KeyType x,BTree ap)
{
    BTree p;
    p = (BTree)malloc(sizeof(BTNode));
    p->keynum = 1;
    p->parent = NULL;
    p->key[1] = x;
    p->ptr[0] = *T;
    p->ptr[1] = ap;

    if(p->ptr[0])
        p->ptr[0]->parent = p;
    if(p->ptr[1])
        p->ptr[1]->parent = p;
    *T = p;
}

Status InsertBTree(BTree *T,KeyType K,BTree q,int i)
{
    KeyType x;
    BTree ap;
    int finished,s;

    x = K;
    ap = NULL;
    finished = FALSE;

    while(q && !finished){
        Insert(q,i,x,ap);
        if(q->keynum < M)
            finished = TRUE;  //Insert complete
        else{  //split the node *q
            s =ceil((double)M/2);
            split(q,s,&ap);
            x = q->key[s];
            q = q->parent;
            if(q)
                i = Search(q,x);
        }//else
    }//while
    if(!finished)
        NewRoot(T,q,x,ap);
    return OK;
}

Status CreateTalbe(SSTable *L)
{
  /*  int i;
    printf("请输入顺序表的长度:");
    scanf("%d",&L->length);
    for(i = 1;i<=L->length;i++){
        printf("请输入第 %d 个元素的值：",i);
        scanf("%d",&L->elem[i].key);
    }*/
    L->length = 15;
    L->elem[1] = 24;
    L->elem[2] = 45;
    L->elem[3] = 50;
    L->elem[4] = 53;
    L->elem[5] = 100;
    L->elem[6] = 37;
    L->elem[7] = 12;
    L->elem[8] = 61;
    L->elem[9] = 90;
    L->elem[10] = 70;
    L->elem[11] = 3;
    L->elem[12] = 30;
    L->elem[13] = 26;
    L->elem[14] = 85;
    L->elem[15] = 7;
    return OK;
}

Status InitTable(SSTable *L)
{
    (*L).elem = (ElemType *)malloc(100 * sizeof(ElemType));
    if(!(*L).elem)
        exit(OVERFLOW);
    (*L).length = 0;
    return OK;
}

Status CreateBTree(BTree *T,SSTable L)
{
    int i;
    *T = NULL;
    Result R;

    if(L.length){
        for(i = 1;i<=L.length;i++){
            R = SearchBTree(*T,L.elem[i]);
            if(!InsertBTree(T, L.elem[i], R.pt, R.i)){
                printf("插入失败!\n");
                break;
            }
        }
    }
    printf("插入完成\n");
    return OK;
}

void PrintBT_InOrder(BTree T)
{
    int j;
    if(T){
        for(j = 0;j<= T->keynum;j++){
            PrintBT_InOrder(T->ptr[j]);
            if(j < T->keynum)
                printf("%d ",T->key[j+1]);
        }
    }
}
/*******************************主函数部分**************************************/
int main()
{
    SSTable L;
    BTree T;

    printf("\n创建一个顺序表如下：\n");
    InitTable(&L);
    CreateTalbe(&L);

    int i;
    for(i = 1;i<= L.length;i++)
        printf("%d ",L.elem[i]);

    printf("\n\n创建一个B树,依次插入顺序表的元素\n");
    CreateBTree(&T,L);

    printf("\n中序遍历B树：\n");
    PrintBT_InOrder(T);

    printf("\n\n寻找是否存在元素 88 ：\n");
    Result R;
    R = SearchBTree(T,88);
    printf("结果是：%d \n",R.tag);

    printf("\n将该元素 88 插入到B树中：\n");
    InsertBTree(&T, 88, R.pt, R.i);
    printf("插入完成\n");

    printf("\n再次中序遍历B树：\n");
    PrintBT_InOrder(T);
    printf("\n");

}



