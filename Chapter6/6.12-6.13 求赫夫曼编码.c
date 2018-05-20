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
typedef struct
{
    unsigned int weight;  //权重
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;  //动态分配数组存储赫夫曼树
typedef char **HuffmanCode;  //动态分配数组存储赫夫曼编码表

/*******************************声明部分****************************************/

void HuffmanCoding_1(HuffmanTree *HT,HuffmanCode *HC,int *w,int n);
//w存放n个字符的权重值（均>0），构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
void Select (HuffmanTree *HT,int i,int *S1,int *S2);
//在HT[1...n]中选择parent为0且weight最小的两个结点，其序号分别为S1，S2
void HuffmanCoding_2(HuffmanTree *HT,HuffmanCode *HC,int *w,int n);
//w存放n个字符的权重值（均>0），构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
void PrintfCode(HuffmanCode HC,int n);
//打印赫夫曼编码

/*******************************函数部分****************************************/

int min(HuffmanTree *HT,int i)
{
    int k,j,flag;
    k = 100;  //预设一个最大值
    for(j = 1;j<= i;j++){
        if((*HT)[j].weight < k && (*HT)[j].parent == 0){
            k = (*HT)[j].weight;
            flag = j;
        }
    }//for
    (*HT)[flag].parent = 1;
    return flag;
}

void Select(HuffmanTree *HT,int i,int *S1,int *S2)
{
    int j;
    *S1 = min(HT,i);
    *S2 = min(HT,i);

    if(*S1 > *S2){
        j = *S1;
        *S1 = *S2;
        *S2 = j;
    }
}

void HuffmanCoding_1(HuffmanTree *HT,HuffmanCode *HC,int *w,int n)
{
    int m,i,s1,s2,start,c,f;
    char *cd;
    if(n<=1)
        return;
    m = 2*n-1;
    *HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));  //0号单元未用

    for(i = 1; i<=n; i++){
        (*HT)[i].weight = w[i-1];
        (*HT)[i].parent = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].lchild = 0;
    }

    for(; i<=m; i++){
        (*HT)[i].weight = 0;
        (*HT)[i].parent = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].lchild = 0;
    }
    printf("HT的初态：\n");
    printf("   weight  parent  lchild   rchild\n");
    for(i = 1;i<=m;i++){
        printf("%2d   %2d     %2d      %2d       %2d  \n",i,(*HT)[i].weight,(*HT)[i].parent,
               (*HT)[i].lchild,(*HT)[i].rchild);
    }
    for(i = n+1;i<=m;i++){   //建赫夫曼树
        Select(HT,i-1,&s1,&s2);
        (*HT)[s1].parent = i;
        (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight+(*HT)[s2].weight;
    }


    //---------从叶子到根逆向求每个字符的赫夫曼编码---------
    *HC = (HuffmanCode)malloc((n+1)*sizeof(char*));  //分配n个字符编码的头指针向量
    cd = (char *)malloc(n*sizeof(char));   //分配求编码的工作空间
    cd[n-1] = '\0';  //编码结束符
    for(i = 1;i<=n;++i){   //逐个字符求赫夫曼编码
        start = n-1;  //编码结束符位置
        for(c = i,f = (*HT)[i].parent; f!=0;c = f,f = (*HT)[f].parent){  //从叶子到根逆向求编码
            if((*HT)[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }
        (*HC)[i] = (char *)malloc((n-start) * sizeof(char));  //为第i个字符编码分配空间
        strcpy((*HC)[i],&cd[start]);
    }
    free(cd);  //释放工作空间
    printf("\n\nHT的终态：\n");
    printf("   weight  parent  lchild   rchild\n");
    for(i = 1;i<=m;i++){
        printf("%2d   %2d     %2d      %2d       %2d  \n",i,(*HT)[i].weight,(*HT)[i].parent,
               (*HT)[i].lchild,(*HT)[i].rchild);
    }
}

void HuffmanCoding_2(HuffmanTree *HT,HuffmanCode *HC,int *w,int n)
{
    int m,i,s1,s2,start,c,f;
    int p,cdlen;
    char *cd;
    if(n<=1)
        return;
    m = 2*n-1;
    *HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));  //0号单元未用

    for(i = 1; i<=n; i++){
        (*HT)[i].weight = w[i-1];
        (*HT)[i].parent = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].lchild = 0;
    }

    for(; i<=m; i++){
        (*HT)[i].weight = 0;
        (*HT)[i].parent = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].lchild = 0;
    }
    for(i = n+1;i<=m;i++){   //建赫夫曼树
        Select(HT,i-1,&s1,&s2);
        (*HT)[s1].parent = i;
        (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight+(*HT)[s2].weight;
    }

    //------------无栈非递归遍历赫夫曼树，求赫夫曼编码------------
    *HC = (HuffmanCode)malloc((n+1) * sizeof(char *));
    cd = (char*)malloc(n*sizeof(char));

    p = m;
    cdlen = 0;

    for(i = 1;i <= m;++i)
        (*HT)[i].weight = 0;  //遍历赫夫曼树时用作结点状态标志
    while(p){
        if((*HT)[p].weight == 0){   //向左
            (*HT)[p].weight = 1;

            if((*HT)[p].lchild != 0){
                p = (*HT)[p].lchild;
                cd[cdlen++] = '0';
            }//if

            else if((*HT)[p].rchild == 0){  //登记叶子结点的字符的编码
                (*HC)[p] = (char*)malloc((cdlen+1)*sizeof(char));
                cd[cdlen] = '\0';
                strcpy((*HC)[p],cd);
            }//else if

        }//if
        else if((*HT)[p].weight == 1){  //向右

            (*HT)[p].weight = 2;
            if((*HT)[p].rchild != 0){
                p = (*HT)[p].rchild;
                cd[cdlen++] = '1';
            }//if
        }//else if

        else{   //HT[p].weight == 2  退回
            (*HT)[p].weight = 0;
            p = (*HT)[p].parent;
            --cdlen;   //退到父结点，编码涨肚减一
        }//else
    }//while
    free(cd);
}

void PrintfCode(HuffmanCode HC,int n)
{
    int i;
    printf("编码为:\n");
    for(i=1;i<=n;i++)
        printf(" %s /",HC[i]);
}

/*******************************主函数部分**************************************/
int main()
{
    int i;
    HuffmanTree HTree1,HTree2;
    HuffmanCode HCode1,HCode2;
    int w1[8] = {5,29,7,8,14,23,3,11};   //对应书上P148 例6-2
    printf("\n使用第一种方法，从叶子到根逆向求每个字符的赫夫曼编码\n");
    HuffmanCoding_1(&HTree1,&HCode1,w1,8);
    PrintfCode(HCode1,8);
    printf("\n\n");

    int w2[4] = {7,5,2,4};  //对应书上 P146 图6.25 的ABCD
    printf("\n使用第二种方法，无栈非递归遍历赫夫曼树，求赫夫曼编码\n");
    HuffmanCoding_2(&HTree2,&HCode2,w2,4);
    PrintfCode(HCode2,4);
    printf("\n\n");
	return 0;
}
