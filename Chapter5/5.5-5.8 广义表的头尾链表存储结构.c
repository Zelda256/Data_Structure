#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAXSIZE 40
#define MAXSTRLEN 6 //最大字符串

typedef int Status;
typedef int ElemType;
typedef char SString[MAXSIZE+1];
typedef char AtomType;
typedef enum{ATOM,LIST}ElemTag;  //ATOM==0:原子，LIST==1：子表

typedef struct GLNode
{
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
int GListDepth(GList L);
//求广义表L的深度
Status CopyGList(GList *T,GList L);
//由广义表L复制得到广义表T
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
       //     SubString(sub,S,2,StrLength(S)-2);  //脱外层括号
            StrCopy(sub,S);
      /*      int i = 0;
            for(i = 0;i<=sub[0];i++)
                printf("sub[%d] = %c \n ",i,sub[i]);*/


            do{  //重复建立n个子表
                sever(&hsub,&sub);   //从sub中分离出表头串husb
            /*    int i = 0;
                for(i = 0;i<=hsub[0];i++)
                printf("hsub[%d] = %c \n ",i,hsub[i]);*/
                CreateCList(&(p->ptr.hp),hsub);
              //  q = p;
                if(StrCompare(sub,emp)){  //表尾不空
                    q = p;
                    p = (GList)malloc(sizeof(GLNode));
                    p->tag = LIST;
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
   /* do{
        ++i;
        SubString(ch,str,i,1);
        if(ch[1] == '(')
            ++k;
        else if(ch[1] == ')')
            --k;
    }while(i<n && (ch[1]!=',' || k != 0));*/
    while(i<n && (ch[i]!=',' || k != 0)){
        if(ch[i] == '(')
            k++;
        else if(ch[i] == ')')
            k--;
        i++;
    }
  //  printf("i = %d\n",i);

    if(i<n){
        SubString(*hstr,ch,1,i-1);
      //  SubString(hstr,str,1,i-1);
      //  SubString(str,str,i+1,n-i);
    }
    else{
        StrCopy(*hstr,ch);
        //StrCopy(hstr,str);
        //ClearString(str);
    }
 //   printf("len = %d\n",*hstr[0]);
/*    int ct = 0;
    for(ct = 0;ct<=*hstr[0];ct++)
        printf("hsub[%d] = %c \n ",ct,hstr[ct]);*/
    StrDelete(*str,2,i);
}

int GListDepth(GList L)
{
    int max,dep;
    GList p;
    if(!L)
        return ERROR;
    if(L->tag == ATOM)
        return 0;
    for(max = 0,p = L; p ;p = p->ptr.tp){
        dep = GListDepth(p->ptr.hp);
        if(dep > max)
            max = dep;
    }
    return max+1;
}

Status CopyGList(GList *T,GList L)
{
    if(!L)
        *T = NULL;
    else{
        *T = (GList)malloc(sizeof(GLNode));
        if(!(*T))
            exit(OVERFLOW);
        (*T)->tag = L->tag;
        if(L->tag == ATOM)
            (*T)->atom = L->atom;  //复制单原子
        else{
            CopyGList(&(*T)->ptr.hp,L->ptr.hp);
            CopyGList(&(*T)->ptr.tp,L->ptr.tp);
        }//else
    }//else
    return OK;
}
/*******************************主函数部分**************************************/

int main()
{
    SString S;
    GList L,T;
    int depth;

    char *chars = "((),(e),(a,(b,c,d)))";
    StrAssign(&S,chars);
    CreateCList(&L,S);
    depth = GListDepth(L);
    printf("广义表L为((),(e),(a,(b,c,d)))\n");
    printf("L的深度为%d\n",depth);

    CopyGList(&T,L);
    printf("\n复制广义表L到T\n");
    printf("T的深度为%d\n",GListDepth(T));
    return 0;
}


