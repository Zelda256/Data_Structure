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
typedef int KeyType;
typedef struct
{
    KeyType key;
}ElemType;

#define EQ(a,b) ((a) == (b))
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1
#define NULLKEY 0

typedef struct
{
    ElemType *elem;  //数据元素存储基址，动态分配数组
    int count;  //当前数据元素个数
    int sizeindex;  //hashsize[sizeindex]为当前容量
}HashTable;   //哈希表

int hashsize[] = {101,211,307,401,503,601,701,809,907,997};
//哈希容量递增表，一个合适的素数序列
int SIZE = 0; //哈希表的容量
/*******************************声明部分****************************************/
Status InitHashTable(HashTable *H);
//initialize a HashTable
unsigned Hash(KeyType key);
//get the hash address
void collision(int *p,int c);
//get next search address p
Status SearchHash(HashTable H,KeyType K,int *p,int *c);
//search an elem.key == K in hash table,if success,use p point to this elem address
//in hashTable,return SUCCESS,else use p point to the insert address,return UNSUCCESS,
//use c to count clash time
Status InsertHash(HashTable *H,ElemType e);
//when SearchHash UNSUCCESS,insert ElemType e into HashTable H,if clash time too much
//Recreate hash table
Status RecreateHashTable(HashTable *H);
//Recreate hash table
/*******************************函数部分****************************************/
Status InitHashTable(HashTable *H)
{
    int i;
    H->count = 0;
    H->sizeindex = 0;
    SIZE = hashsize[0];
    H->elem = (ElemType *)malloc(SIZE * sizeof(ElemType));
    if(!H->elem)
        exit(OVERFLOW);
    for(i = 0;i < SIZE; i++)
        H->elem[i].key = NULLKEY;
    return OK;
}

unsigned Hash(KeyType key)
{
    return key % SIZE;
}

void collision(int *p,int c)   //开放地址法
{
    *p = (*p + c) % SIZE;
}

Status SearchHash(HashTable H,KeyType K,int *p,int *c)
{
    *p = Hash(K);
    while(H.elem[*p].key != NULLKEY && H.elem[*p].key != K){
        (*c)++;
        if((*c) < SIZE)
            collision(p,*c++);
        else
            break;
    }
    if(EQ(K,H.elem[*p].key)){
        return SUCCESS;  //查找成功
    }
    else
        return UNSUCCESS; //查找失败，p返回插入位置
}

Status InsertHash(HashTable *H,ElemType e)
{
    int c,p;
    c = 0;
    if(SearchHash(*H,e.key,&p,&c))
        return DUPLICATE;
    else if(c < hashsize[H->sizeindex] / 2){
        H->elem[p].key = e.key;
        ++H->count;
        return SUCCESS;
    }
    else{
        RecreateHashTable(H);
        return UNSUCCESS;
    }
}

Status RecreateHashTable(HashTable *H)
{
    int i,count;
    ElemType *p,*elem;

    count = (*H).count;
    elem = (ElemType *)malloc(count * sizeof(ElemType));
    if(!elem)
        exit(OVERFLOW);
    for(i = 0;i<SIZE;i++)
        if(H->elem[i].key != NULLKEY)
        *elem = *((*H).elem + i);
    H->count = 0;
    H->sizeindex++;
    SIZE = hashsize[H->sizeindex];
    p = (ElemType *)realloc(H->elem,SIZE * sizeof(ElemType));
    if(!p)
        exit(OVERFLOW);
    H->elem = p;
    for(i = 0;i<SIZE;i++){
        H->elem[i].key = NULLKEY;
    }
    for(p = elem;p < elem + count;p++)
        InsertHash(H,*p);
}

void TraverseHTable(HashTable H)
{
    int i;
    for(i = 0;i < SIZE;i++)
        if(H.elem[i].key != NULLKEY)
        printf("%d  ",H.elem[i].key);
}
/*******************************主函数部分**************************************/
int main()
{
    HashTable H;
    InitHashTable(&H);

    ElemType a,b,c,d,e;
    a.key = 11;
    b.key = 3;
    c.key = 17;
    d.key = 90;
    e.key = 50;

    InsertHash(&H,a);
    InsertHash(&H,b);
    InsertHash(&H,c);
    InsertHash(&H,d);
    InsertHash(&H,e);

    TraverseHTable(H);
    int *p;
    int *g;
    SearchHash(H,3,p,g);

    return 0;
}




