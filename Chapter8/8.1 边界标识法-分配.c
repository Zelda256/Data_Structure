#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAX 1000
#define E 10
#define FootLoc(p) p+p->size-1
typedef int Status;
typedef int ElemType;

typedef struct WORD  //WORD:内存字类型
{
    union{
        struct WORD *llink;  //头部域，指向前驱结点
        struct WORD *uplink;  //底部域，指向本结点头部
    };
    int tag;  //块标志，0：空闲 1：占用，头部和尾部均有
    int size;  //头部域，块大小
    struct WORD *rlink;  //头部域，指向后继结点
}WORD,head,foot,*Space;  //*Space：可利用空间指针类型

Space p;  //全局变量
/*******************************声明部分****************************************/
void InitSpace(WORD memory[MAX+2]);
//初始化一个内存块
Space AllocBountTag(Space *pav,int n);
//若有不小于n的空闲块，则分配相应的存储块，并返回其首地址；否则返回NULL
//若分配后可利用空间表不空，则pav指向表中刚分配过的结点的后继结点
void PrintLayout(Space p,Space pav);
//打印内存块的空闲块
/*******************************函数部分****************************************/
void InitSpace(WORD memory[MAX+2])
{
    Space pav;
    pav = &memory[0];
    memory[0].llink = pav;
    memory[0].tag = 0;
    memory[0].size = MAX;
    memory[0].rlink = pav;
    memory[MAX-1].uplink = pav;
    memory[MAX-1].tag = 0;
    p = pav;
}

Space AllocBountTag(Space *pav,int n)
{
    Space p,f;
    //查找不小于n的空闲块
    for(p = *pav; p && p->size < n && p->rlink != *pav; p = p->rlink);
    if(!p || p->size <n){  //找不到，返回空指针
        printf("没有可用空闲块\n");
        return NULL;
    }
    //p指向找到的空闲块
    f = FootLoc(p);  //f指向底部
    *pav = p->rlink;   //pav指向*p结点的后继结点
    if(p->size-n <= E){  //整块分配，不保留<=e的剩余量
        if(*pav == p)  //可利用空间表变为空表
            *pav = NULL;
        else{  //在表中删除分配的结点
           (*pav)->llink = p->llink;
            p->llink->rlink = *pav;
        }//else
        p->tag = f->tag = 1;  //修改分配结点的头部和底部标志
    }//if
    else{  //分配该块的后n个字
        f->tag = 1;  //修改分配块的底部标志
        p->size -= n;  //置剩余块的大小
        f = FootLoc(p);   //指向剩余块底部
        f->tag = 0;  //设置剩余块底部
        f->uplink = p;
        p = f+1;  //指向分配块头部
        p->tag = 1;  //设置分配块头部
        p->size = n;
    }//else
    return p;
}

void PrintLayout(Space p,Space pav)
{
    Space r;
    r = pav;
    printf("空闲块起止范围 : |");
    printf("%4d <--> %4d | \n",r-p+1,r+r->size-p);
    while(r->rlink != pav){
        r = r->rlink;
        printf("%4d <--> %4d | \n",r-p+1,r+r->size-p);
    }
}

/*******************************主函数部分**************************************/

int main()
{
    Space pav,p1,p2;
    WORD memory[MAX];
    InitSpace(memory);
    pav = p;
    printf("\n初始化一个内存块pav:\n");
    PrintLayout(p,pav);

    p1 = AllocBountTag(&pav,100);
    printf("\n申请大小为100的内存块p1:\n");
    PrintLayout(p,pav);

    p2 = AllocBountTag(&pav,300);
    printf("\n申请大小为300的内存块p2:\n");
    PrintLayout(p,pav);


    return 0;
}



