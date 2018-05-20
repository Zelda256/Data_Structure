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

#define M 3  //可利用空间总容量64K字的2的幂次，子表的个数为M+1 //书上为16

typedef int Status;
typedef int ElemType;
typedef struct WORD_b
{
    struct WORD_b *llink;  //指向前驱结点
    int tag;  //块标志，0：空闲，1：占用
    int kval;  //块大小，值为2幂次K
    struct WORD_b *rlink;  //头部域，指向后继结点
}WORD_b,head;  //WORD：内存字类型，结点的第一个字也称为head
typedef struct HeadNode
{
    int nodesize;  //该链表的空闲块大小
    WORD_b *first;  //该链表的表头指针
}FreeList[M+1];  //表头向量类型

WORD_b *start,*end;
/*******************************声明部分****************************************/
void InitSpace_b(FreeList avail);
//初始化一个内存块
WORD_b* AllocBuddy(FreeList avail,int n);
//avail[0...M]为可利用空间表，n为申请分配量，若有不小于n的空闲块，
//则分配相应的存储块，并返回其首地址，否则返回NULL
void PrintLayout_b(FreeList avail);
//打印内存块的空闲块
/*******************************函数部分****************************************/
void InitSpace_b(FreeList avail)
{
    int k;
    WORD_b *r;

    for(k = 0;k<=M;k++){
        avail[k].nodesize = (int)pow(2,k);
        avail[k].first = NULL;
    }
    r = (WORD_b *)malloc((int)pow(2,M) * sizeof(WORD_b));
    r->llink = r->rlink = r;
    r->tag = 0;
    r->kval = M;
    avail[M].first = r;

    start = r;
    end = r + avail[M].nodesize-1;
}

WORD_b* AllocBuddy(FreeList avail,int n)
{
    int k,i;
    WORD_b *pa,*pre,*suc,*pi;

    //查找满足分配要求的子表
    for(k = 0;k<=M && (avail[k].nodesize < n || !avail[k].first); ++k);

    if(k > M)
        return NULL; //分配失败，返回NULL
    else{  //进行分配
        pa = avail[k].first;  //指向可分配子表的第一个结点
        pre = pa->llink;
        suc = pa->rlink;  //分别指向前驱和后继

        if(pa == suc)
            avail[k].first = NULL;  //分配后该子表变成空表
        else{   //从子表删去*pa结点
            pre->rlink = suc;
            suc->llink = pre;
            avail[k].first = suc;
        }//else

        for(i = 1; k-i >= 0 && avail[k-i].nodesize >= n; ++i){
            pi = pa+(int)pow(2,k-i);
            pi->rlink = pi;
            pi->llink = pi;
            pi->tag = 0;
            pi->kval = k-i;
            avail[k-i].first = pi;
        }//for
        pa->tag = 1;
        pa->kval = k-(--i);
    }//else
    return pa;
}

void PrintLayout_b(FreeList avail)
{
    int k;
    WORD_b *r;
    int mark;

    for(k = 0,mark = 0;k<=M;k++){
        if(avail[k].first){
            mark = 1;
            break;
        }
    }

    if(!mark)
        printf("内存已被占用完!\n");
    else{
         printf("空闲块起止范围 : ");
         for(k = 0;k<=M;k++){
            r = avail[k].first;
            if(r){
                printf("| %d <--> %d |",r-start+1,r+(int)pow(2,r->kval)-start);
                while(r->rlink != avail[k].first){
                    r = r->rlink;
                    printf("| %d <--> %d |\n",r-start+1,r+(int)pow(2,r->kval)-start);
                }//while
            }//if
         }//for
    }//else
    printf("\n");

}
/*******************************主函数部分**************************************/
int main()
{
    FreeList avail;
    WORD_b *p1,*p2;

    InitSpace_b(avail);
    printf("\n初始化了一块内存\n");
    PrintLayout_b(avail);

    p1 = AllocBuddy(avail,1);
    printf("\n申请了大小为 1 的内存p1\n");
    PrintLayout_b(avail);

    p2 = AllocBuddy(avail,2);
    printf("\n申请了大小为 2 的内存p2\n");
    PrintLayout_b(avail);

    return 0;
}



