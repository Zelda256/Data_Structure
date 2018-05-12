#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <conio.h>
#include <ctype.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

#define MaxBookNum 1000 //假设只对1000本书建立索引表(1000)
#define MaxKeyNum 2500  //索引表的最大容量(2500)
#define MaxLineLen 500  //书目串的最大长度(500)
#define MaxWordNum 10  //词表的最大容量
#define MaxWordLength 30 //单词的最大长度

typedef int Status;
typedef int ElemType; //定义链表的数据元素类型为整型
typedef int Boolean;

typedef struct
{
    char item[MaxWordNum][MaxWordLength]; //字符串的数组
    int last;  //词表的长度
}WordListType;  //词表的类型（顺序表）

typedef struct
{
    char *ch;  //如果是非空串，则按串长分配存储区，否则ch为NULL
    int length;  //串长度
}HString;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*Link,*Position;

typedef struct
{
    Link head,tail;
    int len;
}LinkList;

typedef struct
{
    HString key;   //关键词
    LinkList bnolist;  //存放书号索引的链表
}IdxTermType;  //索引项类型

typedef struct
{
    IdxTermType item[MaxKeyNum+1];
    int last;
}IdxListType;   //索引表类型

//----------------主要变量--------------
char buf[MaxLineLen];  //书目串缓冲区
WordListType wdlist;  //关键字词表
IdxListType idxlist;  //索引表
char oftenwords[6][10] = {"an","a","of","and","to","the"};

/*******************************声明部分****************************************/

//--------------基本操作---------

void InitIdxList (IdxListType *idxlist);
//初始化操作，置索引表idxlist为空表，且在idxlist.item[0]设一空串

void GetLine (FILE *f);
//从文件F读入一个书目信息到书目串缓冲区buf

void ExtractKeyWord (int *Num);
//Status ExtractKeyWord(char* Buffer,WordListType *w,int *Num);
//从buf中提取书名关键词到词表wdlist，书号存入bno

Status InsIdxList (IdxListType *idxlist,ElemType bno);
//将书号为bno的书名关键词按词典顺序插入索引表idxlist

void PutText (FILE *g,IdxListType idxlist);
//将生成的索引表idxlist输出到文件g

//--------------为实现在索引表上进行插入，要先实现下列操作-----------

void GetWord (int i,HString *wd);
//用wd返回词表wdist中第i个关键词

int Locate (IdxListType *idxlist,HString wd,Boolean *b);
//在索引表idxlist中查询是否存在与wd相等的关键词。若存在，则返回其在索引表
//中的位置，且b取值TRUE；否则返回插入位置，且b取值FALSE

void InsertNewKey(int j,HString wd);
//在索引表idxli的第i项上插入新关键词wd，并初始化书号索引的链表为空表

Status InsertBook (int i,int bno);
//在索引表idxlist的第i项中插入书号为bno的索引

//------------串的堆分配存储表示-----------

Status StrAssign(HString *T,char *chars);
//生成一个其值等于串常量chars的串T

int StrCompare(HString S,HString T);
//若S>T，则返回值>0,若S=T，则返回值 = 0，若S<T，则返回值<0

Status StrCopy(HString *T, HString S);
//由串S复制得串T

//----------------带头结点的线性链表-------------

Status InitList(LinkList *L);
//构造一个空的线性链表L

Status MakeNode(Link *p,ElemType e);
//分配由p指向值e的结点，并返回OK；若分配失败，则返回ERROR

Status Append (LinkList *L,Link s);
//将指针s所指的一串结点链接在线性链表L的最后一个结点
//之后，改变链表L的尾指针指向新的尾结点

/*******************************函数部分****************************************/

Status StrAssign(HString *T,char *chars)
{
    int i = strlen(chars);
    if((*T).ch)
        free((*T).ch);
    if(!i){  //若chars为空
        (*T).ch = NULL;
        (*T).length = 0;
    }
    else{  //chars不空
        if(!((*T).ch = (char *)malloc(i * sizeof(char))))  //为T分配chars所需的存储空间
            exit(OVERFLOW);
        int count;
        for(count = 0;count <= i;count++) //把chars存入T中
            (*T).ch[count] = chars[count];
        (*T).length = i;
    } //else
    return OK;
}

void InitString(HString *T)
{
    (*T).length = 0;
    (*T).ch = NULL;
}

int StrCompare(HString S,HString T)
{
    int count;
    for(count = 0;count<S.length && count<T.length;count++){
        if(S.ch[count] != T.ch[count])
                return S.ch[count]-T.ch[count] ;
    }
    return S.length-T.length;
}

Status StrCopy(HString *T, HString S)
{
    int j;
    if((*T).ch)
        free((*T).ch);  //删除T串中原有值
    (*T).ch = (char*)malloc(S.length * sizeof(char));
    if(!(*T).ch)
        exit(OVERFLOW);
    for(j = 0; j <= S.length; j++)
        (*T).ch[j] = S.ch[j];
    (*T).length = S.length;
    return OK;
}

Status InitList(LinkList *L)
{
    Link p;
    p = (Link)malloc(sizeof(LNode));
    if(!p)
        exit(OVERFLOW);
    p->next = NULL;
    (*L).head = (*L).tail = p;
    (*L).len = 0;
    return OK;
}

Status MakeNode(Link *p,ElemType e)
{
    *p = (Link)malloc(sizeof(LNode));
    if(!(*p))
        exit(OVERFLOW);
    (*p)->data = e;
    (*p)->next = NULL;
    return OK;
}

Status Append (LinkList *L,Link s)
{
    int i = 1;
    (*L).tail->next = s;
    while(s->next){
        s = s->next;
        i++;
    }
    (*L).tail = s;
    (*L).len += i;
    return OK;
}

void GetWord(int i,HString *wd)
{
    char *p;
    p = *(wdlist.item +i);
    StrAssign(wd,p);  //生成关键字字符串
}

int Locate(IdxListType *idxlist,HString wd,Boolean *b)
{
    int i,m;
    for(i = (*idxlist).last-1; ( m=StrCompare((*idxlist).item[i].key,wd) ) >0; --i);

    if(m == 0){   //找到
        *b = TRUE;
        return i;
    }
    else{
        *b = FALSE;
        return i+1;
    }
}

void InsertNewKey(int j,HString wd)
{
    int count;
    InitList(&idxlist.item[idxlist.last+1].bnolist);
    for(count = idxlist.last-1; count>=j; --count){  //后移索引项
        idxlist.item[count+1] = idxlist.item[count];
    }
    InitString(&idxlist.item[j].key);
    StrCopy(&idxlist.item[j].key,wd);  //插入新的索引项 //串赋值
    InitList(&idxlist.item[j].bnolist);  //初始化书号索引表为空表
    ++idxlist.last;
}

Status InsertBook (int i,int bookno)
{
    Link p;
    if(!MakeNode(&p,bookno))
        return ERROR;
    Append(&idxlist.item[i].bnolist,p);
    return OK;
}

Status InsertIdxList(IdxListType *idxlist,int bno)
{
    int i,j;
    HString wd;
    Boolean b;
    InitString(&wd);
    for(i= 0;i<wdlist.last;++i){
        GetWord(i,&wd);    //获取wdlist中保存的单词
        j = Locate(idxlist,wd,&b);   //查找是否已存在于idxlist中
        if(!b)  //不存在
            InsertNewKey(j,wd);  //则插入新的关键词
        InsertBook(j,bno);  //插入书号
    }
    return OK;
}

void InitIdxList (IdxListType *idxlist)
{
    int i;
    (*idxlist).last = 0;
    for(i = 0;i<MaxKeyNum;i++){
        InitList(&(*idxlist).item[i].bnolist); //初始化索引表项目中的书号的链表
    }
}

void ExtractKeyWord (int *BookNum)
{
    int i = 0,j = 0,k = 0,m;
    wdlist.last = 0;  //很重要
    Boolean Ignore;
    char TempChar[30];
    for(m = 0;m<=30;m++)
        TempChar[m] = '\0';   //清空TempChat[]
    while(*(buf+i) != ' '){  //提取书目串缓冲区其中的书号
        TempChar[i] = *(buf+i); //将书号以字符串类型保存在该数组中
        i++;
    }
    TempChar[i] = '\0';
    *BookNum = atoi(TempChar); //将书号转为int

    for(m = 0;m<=i;m++)
        TempChar[m] = '\0';   //清空TempChat[]
    i++;  //推进一位，当前*(buf+i)开始为书名
    while(*(buf+i) != '\n' && *(buf+i) != '\0'){
        //每个字符串末尾都有结束符\n
        if(*(buf+i) != ' '){  //若非空字符
            if(*(buf+i) >= 'A' && *(buf+i) <= 'Z'){
                *(buf+i) -= 'A' - 'a';  //若为大写，则转为小写
            }
            TempChar[j] = *(buf+i);  //把当前字符加入TempChar中//------------
            j++;
            i++;
        } //if
        else{  //若为空字符，则检索当前TempChar中保存的字符串是否为常用词
            Ignore = FALSE;  //若Ignore为TRUE，则为常用词；为FALSE则不是常用词

            for(m = 0;m<6;m++){     //查找是否为常用词
                if(strcmp(TempChar,oftenwords[m]) == 0){
                    Ignore = TRUE;  //是常用词
                    break;
                }//if
            }//for
            if(Ignore){
               for(m = 0;m<=j;m++)
                    TempChar[m] = '\0';   //清空TempChat[]
                i++;
                j = 0;
            }//if
            else{  //不是常用词
                for(m = 0;m<=j;m++)  //将该词插入wdlist中
                    wdlist.item[wdlist.last][m] = TempChar[m];
                for(m = 0;m<=j;m++)
                    TempChar[m] = '\0';   //清空TempChat[]
                k++;
                wdlist.last++;
                i++;
                j=0;
            }//else
        }//else

    }//while
}

void GetLine(FILE *f)
{
    fgets(buf,MaxLineLen,f);
}

void PutText (FILE *g,IdxListType idxlist)
{
    int i,j,k;
    Link p;
    for(i = 0;i<=idxlist.last;i++){
        for(j = 0;j<idxlist.item[i].key.length; j++)
            putc(*(idxlist.item[i].key.ch + j),g);
        putc('\t',g);
        if(idxlist.item[i].key.length < 8)
            putc('\t',g);
        p = idxlist.item[i].bnolist.head;
        for(k = 0;k<idxlist.item[i].bnolist.len ; k++){
            p = p->next;
            fprintf(g,"%03d",p->data);
            putc(' ',g);
        }//for
        putc('\n',g);
    }//for
}

void PrintFile(FILE *FileName)
{
    char ch;
    rewind(FileName);
    ch = getc(FileName);
    while(ch != EOF){
        putchar(ch);
        ch = getc(FileName);
    }
    printf("\n");
    rewind(FileName);
}

/*******************************主函数部分**************************************/

int main()
{
    FILE *f,*g;
    int ct;
    int BookNo;
    if((f = fopen("BookName.txt","r")) == NULL){
        printf("ERROR in open BookName.txt\n");
        exit(1);
    }
    if((g = fopen("KeyWordIndex_self.txt","w"))==NULL){
        printf("ERROR in open KeyWordIndex_self.txt\n");
        exit(1);
    }
    printf("书单文件：\n");
    PrintFile(f);
    InitIdxList(&idxlist);
    WordListType w;
    while(!feof(f)){
        GetLine(f);   //读取书单文件中的一行到缓冲区
        ExtractKeyWord(&BookNo);
        InsertIdxList(&idxlist,BookNo);
    }
    PutText(g,idxlist);
    fclose(f);
    fclose(g);
    printf("\n结果如下：\n");
    if((g = fopen("KeyWordIndex_self.txt","r"))==NULL){
        printf("ERROR in open KeyWorkIndex_self.txt\n");
        exit(1);
    }
    PrintFile(g);
    fclose(g);
    return 0;
}
