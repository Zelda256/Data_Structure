#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;
typedef int ElemType;

#define MAX_NUM_OF_KEY 8  //关键字项数最大值
#define RADIX 10  //关键字基数，此时是十进制整数的基数
#define MAX_SPACE 100  //书上为10000
#define ord(ch) ((ch)-'0')
#define succ(x) ((x)+1)
typedef char KeyType;
typedef struct
{
    KeyType keys[MAX_NUM_OF_KEY];  //关键字
    int next;
}SLCell;   //静态链表的结点类型

typedef struct
{
    SLCell r[MAX_SPACE];  //静态链表的可利用空间，r[0]为头结点
    int keynum;  //记录当前关键字个数
    int recnum;  //静态链表的当前长度
}SLList;   //静态链表类型
typedef int ArrType[RADIX];  //指针数组类型

/*******************************声明部分****************************************/



/*******************************函数部分****************************************/
void Distribute(SLCell r[],int i,ArrType f,ArrType e)
{
    int j,p;

    for(j = 0;j<RADIX;++j){
        f[j] = 0;
        e[j] = 0;
    }

    for(p = r[0].next; p ;p = r[p].next){
        j = ord(r[p].keys[i]);
        if(!f[j])
            f[j] = p;
        else
            r[e[j]].next = p;
        e[j] = p;
    }
}

void Collect(SLCell r[],int i,ArrType f,ArrType e)
{
    int j,t;

    for(j = 0; j<RADIX&&!f[j] ; j = succ(j));  //找到第一个非空子表，succ为求后继函数
    if(j<RADIX){
        r[0].next = f[j];
        t = e[j];
        while(j<RADIX){
            for(j = succ(j) ; j<RADIX-1 && !f[j]; j = succ(j));
                if(f[j] && j<=RADIX-1){
                    r[t].next = f[j];
                    t = e[j];
                }
        }
        r[t].next = 0;
    }

}

void RadixSort(SLList *L)
{
    int i;
    ArrType f,e;

    for(i = 0;i<L->keynum;i++){
        Distribute(L->r,i,f,e);
        Collect(L->r,i,f,e);
    }
}

void CreateSLL(SLList *L)
{
    char s[100];
    int i,n,ct;
    L->recnum = 0;

 /*   printf("请输入关键字个数：\n");
    scanf("%d",&L->keynum);
    printf("请输入链表长度：\n");
    scanf("%d",&n);*/
    L->keynum = 3;
    n = 10;
    printf("依次输入:278 109 063 963 589 184 505 269 008 083 \n");
    for(ct = 0;ct<n;ct++){
    //    printf("请输入关键字：\n");

        scanf("%s",&s);
        L->recnum++;
        for(i = 0;i<L->keynum;++i)
            L->r[L->recnum].keys[L->keynum-1-i] = s[i];
    }
    for(i = 0;i<L->recnum;++i)
        L->r[i].next = i+1;
    L->r[L->recnum].next = 0;
}

void TraverseSLL(SLList L)
{
    int i,j;
    for(i = L.r[0].next; i ;i = L.r[i].next){
        for(j = L.keynum-1;j>=0;j--)
            printf("%c",L.r[i].keys[j]);
        printf("  ");
    }
    printf("\n");
}
/*******************************主函数部分**************************************/
int main()
{
    SLList L;
    printf("创建静态链表\n");
    CreateSLL(&L);
    printf("创建完成：\n");
    TraverseSLL(L);

    printf("\n基数排序：\n");
    RadixSort(&L);
    TraverseSLL(L);
    return 0;
}



