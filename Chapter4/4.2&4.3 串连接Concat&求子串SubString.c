/*  串的定长顺序存储表示  */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40
#define MAXSTRLEN 6 //最大字符串
typedef int Status;
typedef char SString[MAXSIZE+1];
//此处声明的SString[maxsize+1]虽是数组，在SubString中作为指针使用，

//因位是指针，SString[0]存放实际数组的地址，使用时不用加*或&，直接传入数组的值

/*******************************声明部分****************************************/
Status StrAssign(SString *T,char *chars);
//生成一个其值等于chars的串T  第一个元素为字符串长度
Status SubString(SString Sub, SString T,int pos,int len);
//用Sub返回串T的第pos个字符起长度为len的子串
Status Concat(SString T,SString S1,SString S2);
//用T返回由S1和S2连接而成的新串

/*Status SubString(SString Sub, SString T,int pos,int len)*/
int StrCompare(SString S,SString T);
int StrLength(SString S);
int StrEmpty(SString S);
Status StrCopy(SString S,SString *T);
Status ClearString(SString S);

/*******************************函数部分****************************************/

Status StrAssign(SString *T,char *chars)
{
    int i,ct;
    for(i = 0;i <= MAXSIZE; i++)
        (*T)[i] = '\0';    //全部清零

    (*T)[0] = strlen(chars);
    for(ct = 1;*chars != '\0';ct++,chars++){
        (*T)[ct] = *chars;
    }
    return OK;
}

Status SubString(SString Sub, SString T,int pos,int len)
{
    if(pos<1 || pos>T[0] || len<0 || len>T[0]-pos+1)
        return ERROR;

    int ct,cnt;
    for(ct = 1,cnt = pos;cnt <= len+pos;ct++,cnt++){
        Sub[ct]=T[cnt];
    }
    Sub[0] = len+1;
    return OK;
}
/*
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
*/
Status Concat(SString T,SString S1,SString S2)
{
    int count,i;
    int uncut;
    //情况一：若不用截断，直接复制S1和S2到T中
    if(S1[0]+S2[0] <= MAXSTRLEN){
        T[0] = S1[0] + S2[0];
        for(count = 1;count <= S1[0];count++){   //复制S1的值到T中
            T[count] = S1[count];
        }
        for(count = S1[0]+1,i = 1;count <= T[0];count++,i++){ //复制S2的值到T中
            T[count] = S2[i];
        }
        uncut = TRUE;
    }//if

    //情况二：因为长度超出限制，需截断S2后面的子串
    else if( S1[0] < MAXSTRLEN){
        T[0] = MAXSTRLEN;
        for(count = 1;count <= S1[0];count++){   //复制S1的值到T中
            T[count] = S1[count];
        }
        for(count = S1[0]+1,i = 1;count <= T[0];count++,i++){ //复制截断的S2的值到T中
            T[count] = S2[i];
        }
        uncut = FALSE;
    }//else if

    //情况三：因为S1的长度已经达到最大长度，T只取S1
    else{
        T[0] = MAXSTRLEN;
        for(count = 1;count <= S1[0];count++){   //复制S1的值到T中
            T[count] = S1[count];
        }
    }//else
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

int StrEmpty(SString S)
{
    return S[0] == 0;
}

Status StrCopy(SString S,SString *T)
{
    int i;
    for(i = 0;i<=S[0];i++)
        (*T)[i] = S[i];
    return OK;
}

Status ClearString(SString S)
{
    S[0] = 0;
}
/*******************************主函数部分**************************************/
int main()
{
    SString T,S1,S2;
    //验证情况一
    /*char *chars1 = "abcd";
    char *chars2 = "e";*/


    //验证情况二
   /* char *chars1 = "abcd";
    char *chars2 = "efghijk";*/

    //验证情况三
    char *chars1 = "abcdef";
    char *chars2 = "efghijk";


    StrAssign(&S1,chars1);
    StrAssign(&S2,chars2);
    Concat(T,S1,S2);

    //打印T中的值
    int i;
    for(i = 1;i<=T[0];i++)
        printf("%c",T[i]);

    return 0;
}




