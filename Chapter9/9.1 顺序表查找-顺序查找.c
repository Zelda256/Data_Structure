#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100 //存储空间的初始分配量

#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a) <  (b))
#define LQ(a,b) ((a) <= (b))

typedef int Status;
typedef int KeyType;
typedef struct
{
    KeyType key;
    int weight;
}ElemType;
typedef struct
{
    ElemType *elem; //unit elem[0] keep NULL
    int length;   //length of table
}SSTable;

/*******************************声明部分****************************************/
Status InitTable(SSTable *L);
Status CreateTalbe(SSTable *L);
int Serch_Seq(SSTable ST,KeyType key);
//在顺序表ST中顺序查找其关键字等于key的数据元素
/*******************************函数部分****************************************/
Status InitTable(SSTable *L)
{
    (*L).elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!(*L).elem)
        exit(OVERFLOW);
    (*L).length = 0;
    return OK;
}

Status CreateTalbe(SSTable *L)
{
    int i;
 /*   printf("请输入顺序表的长度:");
    scanf("%d",&L->length);
    for(i = 1;i<=L->length;i++){
        printf("请输入第 %d 个元素的值：",i);
        scanf("%d",&L->elem[i].key);
    }*/
    L->elem[1].key = 5;
    L->elem[2].key = 13;
    L->elem[3].key = 19;
    L->elem[4].key = 21;
    L->elem[5].key = 37;
    L->elem[6].key = 56;
    L->elem[7].key = 64;
    L->elem[8].key = 75;
    L->elem[9].key = 80;
    L->elem[10].key = 88;
    L->elem[11].key = 92;
    L->length = 11;
    return OK;
}

int Serch_Seq(SSTable ST,KeyType key)
{
    int i;
    ST.elem[0].key = 0;  //Set the sentinel //flag
    for(i = ST.length; !EQ(ST.elem[i].key,key); --i);  //从后往前找
    return i;  //找不到时，i = 0；
}

/*******************************主函数部分**************************************/

int main()
{
    SSTable L;
    InitTable(&L);
    CreateTalbe(&L);
    int ct;
    printf("顺序表：");
    for(ct = 1;ct<=11;ct++)
        printf("%d  ",L.elem[ct].key);
    printf("\n寻找 21 的位置: %d",Serch_Seq(L,21));
    return 0;
}


