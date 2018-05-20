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

#define MAXSIZE 40
#define MAXSTRLEN 6 //最大字符串

typedef char SString[MAXSIZE+1];
typedef char AtomType;
typedef enum{ATOM,LIST}ElemTag;  //ATOM==0:原子，LIST==1：子表

typedef struct GLNode
{
    int mark;
    ElemTag tag;  //公共部分，用于区分原子结点和表结点
    union{    //原子结点和表结点的联合部分
        AtomType atom;    //atom是原子结点的值域
        struct{
            struct GLNode *hp,*tp;
        }ptr;  //ptr是表结点的指针域，ptr.hp和ptr.tp分别指向表头和表尾
    };
}GLNode,*GList;  //广义表eixing




/*******************************声明部分****************************************/
Status StrAssign(SString *T,char *chars);
int StrCompare(SString S,SString T);
int StrLength(SString S);
Status SubString(SString Sub, SString T,int pos,int len);
int StrEmpty(SString S);
Status StrCopy(SString T,SString S);
Status ClearString(SString S);
Status StrDelete(SString S,int pos,int len);
Status CreateCList(GList *L,SString S);
//由广义表的书写形式串S创建广义表L
Status sever(SString *hstr,SString *str);
//将非空串str分割成两部分：hstr为第一个','之前的子串，str为之后的子串
void MarkList(GList GL);
//遍历非空广义表GL（GL != NULL 且 GL->mark == 0），对表中所有未加标志的结点加标志
/*******************************函数部分****************************************/
Status StrAssign(SString *T,char *chars)
{
    int i,ct,len;

    len = strlen(chars);
    (*T)[0] = len;
    for(i = 1;i<=len;i++)
        (*T)[i] = chars[i-1];
    return OK;
}

int StrCompare(SString S,SString T)
{

    int i = 1;

    while(i<=S[0] && i<= T[0]){
        if(S[i] == T[i])
            i++;
        else
            return S[i]- T[i];
    }
    return S[0] - T[0];
}

int StrLength(SString S)
{
    return S[0];
}

Status SubString(SString Sub, SString T,int pos,int len)
{
    if(pos<1 || pos>T[0] || len<0 || len>T[0]-pos+1)
        return ERROR;
    int i ;
    for(i = 1;i<=len;i++)
        Sub[i] = T[pos+i-1];
    Sub[0] = len;
    return OK;
}

int StrEmpty(SString S)
{
    return S[0] == 0 ? TRUE : FALSE;
}

Status StrCopy(SString T,SString S)
{
    int i;
    for(i = 0;i<=S[0];i++)
        T[i] = S[i];
    return OK;
}

Status ClearString(SString S)
{
    S[0] = 0;
}

Status StrDelete(SString S,int pos,int len)
{
    int i;
    if(pos <1 || pos+len-1 > S[0] || len<0)
        return ERROR;
    for(i = pos+len;i<=S[0] ;i++)
        S[i-len] = S[i];
    S[0] -= len;
    return OK;
}

Status CreateCList(GList *L,SString S)
{
    SString sub,hsub,emp;
    GList p,q;

    StrAssign(&emp,"()");

    if( ! StrCompare(S,emp))
        *L = NULL; //创建空表

    else{
        *L = (GList)malloc(sizeof(GLNode));

        if(StrLength(S) == 1){
            (*L)->tag = ATOM;
            (*L)->atom = S[1];  //创建单原子广义表
        }
        else{
            (*L)->tag = LIST;
            p = *L;
            StrCopy(sub,S);
            do{  //重复建立n个子表
                sever(&hsub,&sub);   //从sub中分离出表头串husb
                CreateCList(&(p->ptr.hp),hsub);
                if(StrCompare(sub,emp)){  //表尾不空
                    q = p;
                    p = (GList)malloc(sizeof(GLNode));
                    p->tag = LIST;
                    p->mark = 0;
                    q->ptr.tp = p;
                }//if
            }while(StrCompare(sub,emp));
            p->ptr.tp = NULL;
        }//else
    }//else
    return OK;
}

Status sever(SString *hstr,SString *str)
{
    int n,i,k;
    SString ch;
    i = 1;
    k = 0; //k记尚未配对的左括号个数

    SubString(ch,*str,2,StrLength(*str)-2);
    n = StrLength(ch);

    while(i<n && (ch[i]!=',' || k != 0)){
        if(ch[i] == '(')
            k++;
        else if(ch[i] == ')')
            k--;
        i++;
    }

    if(i<n)
        SubString(*hstr,ch,1,i-1);
    else
        StrCopy(*hstr,ch);

    StrDelete(*str,2,i);
}

void MarkList(GList GL)
{
    GList t,p,q;
    Status finished;
    t = NULL;  //t指示p的母表
    p = GL;
    finished = FALSE;
    while(!finished){
        while(p->mark == 0){
            p->mark = 1;
            q = p->ptr.hp;  //q指向*p的表头
            if(q && q->mark == 0){
                if(q->tag == 0)  //ATOM，表头为原子结点
                    q->mark = 1;
                else{      //继续遍历子表
                    p->ptr.hp = t;
                    p->tag = 0;
                    t = p;
                    p = q;
                }//else
            }//if
        }//whie p->mark  //完成对表头的标志
        q = p->ptr.hp;  //q指向*p的表尾
        if(q && q->mark == 0){   //继续遍历表尾
            p->ptr.tp = t;
            t = p;
            p = q;
        }//if
        else{
            while(t && t->tag == 1){  //LIST，表结点，从表尾回溯
                q = t;
                t = q->ptr.tp;
                q->ptr.tp = p;
                p = q;
            }//while
            if(!t)
                finished = TRUE;  //结束
            else{   //从表头回溯
                q = t;
                t = q->ptr.hp;
                q->ptr.hp = p;
                p = q;
                p->tag = 1;
            }//else  //继续遍历表尾
        }//else
    }//while

}
/*******************************主函数部分**************************************/
int main()
{
    SString S;
    GList L;
    char *chars = "((),(e),(a,(b,c,d)))";
    StrAssign(&S,chars);
    CreateCList(&L,S);
    MarkList(L);
    return 0;
}



