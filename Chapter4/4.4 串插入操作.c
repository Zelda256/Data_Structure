/*  串的堆分配存储表示  */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
typedef int Status;
typedef struct
{
    char *ch;  //如果是非空串，则按串长分配存储区，否则ch为NULL
    int length;  //串长度
}HString;

/*******************************声明部分****************************************/

Status StrAssign(HString *T,char *chars);
//生成一个其值等于串常量chars的串T
Status StrInsert (HString *S,int pos,HString T);
//1<=pos<=StrLength(S)+1.在串S的第pos个字符之前插入串T
int StrLength(HString S);
//返回S的元素个数，成为串的长度
int StrCompare(HString S,HString T);
//若S>T，则返回值>0,若S=T，则返回值 = 0，若S<T，则返回值<0
Status ClearString(HString *S);
//将S清空
Status Concat(HString *T,HString S1,HString S2);
//用T返回由S1和S2连接而成的新串
Status SubString(HString *Sub,HString S,int pos,int len);
//用Sub返回串S的第pos个字符起长度为len的子串
//其中,1<= pos<= StrLength(S) 且 0<= len <= StrLength(S)-pos+1
Status StrCopy(HString *T, HString S);
/*******************************函数部分****************************************/

Status StrAssign(HString *T,char *chars)
{
    if((*T).ch){  //释放旧空间
        free((*T).ch);
    }
    int i = strlen(chars);
    if(!i){  //若chars为空
        (*T).ch = NULL;
        (*T).length = 0;
    }
    else{  //chars不空
        if(!((*T).ch = (char *)malloc(i * sizeof(char))))  //为T分配chars所需的存储空间
            exit(OVERFLOW);
        int count;
        for(count = 0;count <= i-1;count++){  //把chars存入T中
            (*T).ch[count] = chars[count];
            (*T).length = i;
        } //for
    } //else
    return OK;
}

int StrLength(HString S)
{
    return S.length;
}

int StrCompare(HString S,HString T)
{
    int count;
    for(count = 0;count < S.length && count < T.length;count++){
        if(S.ch[count] != T.ch[count])
            return S.ch[count] - T.ch[count];
    }
    return S.length - T.length;
}

Status ClearString(HString *S)
{
    if((*S).ch){
        free((*S).ch);
        (*S).ch = NULL;
    }
    (*S).length = 0;
    return OK;
}

Status Concat(HString *T,HString S1,HString S2)
{
    if((*T).ch){  //释放旧空间
        free((*T).ch);
    }
    if(!((*T).ch = (char *)malloc((S1.length+S2.length)* sizeof(char))))
        exit(OVERFLOW);
    int count,cnt;
    for(count = 0;count <= S1.length;count++){  //把S1存入T中
        (*T).ch[count] = S1.ch[count];
    }
    (*T).length = S1.length + S2.length;  //更改T的长度为两串之和
    for(count = S1.length,cnt = 0;count <= (*T).length;count++,cnt++){
        (*T).ch[count] = S2.ch[cnt];  //把S2存入T中
    }
    return OK;
}

Status SubString(HString *Sub,HString S,int pos,int len)
{
    if(pos<1 || pos>S.length || len<0 || len >S.length-pos+1)
        return ERROR;
    if((*Sub).ch){  //释放旧空间
        free((*Sub).ch);
    }
    if(!len){
        (*Sub).ch = NULL;
        (*Sub).length = 0;  //空子串
    }
    else{  //完整子串
        (*Sub).ch = (char *)malloc(len*sizeof(char));
        int count,cnt;
        for(count = 0,cnt = pos-1;count <= len-1;count++,cnt++){
            (*Sub).ch[count] = S.ch[cnt];
        }
        (*Sub).length = len;
    }//else
    return OK;
}

Status StrInsert (HString *S,int pos,HString T)
{
    if(pos<1 || pos >(*S).length+1)
        return ERROR;  //pos不合法
    if(T.length){
        if(!((*S).ch = (char*)realloc((*S).ch,((*S).length + T.length)*sizeof(char))))
            exit(OVERFLOW);
        int count,cnt;
        for(count = (*S).length-1;count>= pos-1;count--){
            (*S).ch[count+T.length-1] = (*S).ch[count];  //为插入T腾出位置
        }
        for(count = pos-1,cnt = 0;cnt<= T.length-1;count++,cnt++)
        (*S).ch[count] = T.ch[cnt];  //插入T
        (*S).length += T.length;
    }//if
    return OK;
}

Status StrCopy(HString *T, HString S){
    int j;
    if((*T).ch)
        free((*T).ch);
    (*T).ch = (char*)malloc(S.length * sizeof(char));
    if(!(*T).ch)
        exit(OVERFLOW);
    for(j = 0; j < S.length; j++)
        (*T).ch[j] = S.ch[j];
    (*T).length = S.length;
    return OK;
}

/*******************************主函数部分**************************************/

int main()
{
    HString T,S,S1,S2,Sub;
    char *charsT = "abcd";
    char *chars1 = "abc";
    char *chars2 = "AAAA";

    StrAssign(&T,charsT);
    StrAssign(&S,chars1);
    StrAssign(&S1,chars1);
    StrAssign(&S2,chars2);
    int count;
    printf("T的长度为：%d\n",T.length);
    printf("T的内容为：");
    for(count = 0;count <T.length;count++){
        printf("%c",T.ch[count]);
    }
    printf("\n");

    printf("\nStrCompare(S,T) = %d\n",StrCompare(S,T));

    Concat(&T,S1,S2);
    printf("\n链接S1，S2为T之后\n");
    printf("T的长度为：%d\n",T.length);
    printf("T的内容为：");
    for(count = 0;count <T.length;count++){
        printf("%c",T.ch[count]);
    }
    printf("\n");

    printf("\nS的长度为：%d\n",S.length);
    printf("S的内容为：");
    for(count = 0;count <S.length;count++){
        printf("%c",S.ch[count]);
    }
    printf("用Sub返回S的第1个字符起长度为2的子串\n");
    SubString(&Sub,S,1,2);
    printf("Sub的长度为：%d\n",Sub.length);
    printf("Sub的内容为：");
    for(count = 0;count <Sub.length;count++){
        printf("%c",Sub.ch[count]);
    }
    printf("\n");

    printf("\n在串S的第1个字符之前插入串T\n");
    StrInsert(&S,1,T);
    printf("S的长度为：%d\n",S.length);
    printf("S的内容为：");
    for(count = 0;count <S.length;count++){
        printf("%c",S.ch[count]);
    }
    return 0;
}

