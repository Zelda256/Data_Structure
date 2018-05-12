//求子串位置的定位函数
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define MAXSTRLEN 255
#define MAXSIZE 40 //最大字符串

typedef int Status;
typedef unsigned char SString[MAXSTRLEN +1];

/*******************************声明部分****************************************/

int Index(SString S,SString T,int pos);
//返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数值为0
//其中，T非空，1<= pos <= StrLength(S)
Status StrAssign(SString T,char *chars);
//生成一个其值等于chars的串T  第一个元素为字符串长度
/*******************************函数部分****************************************/
int Index(SString S,SString T,int pos)
{
    int i = pos,j = 1;
    while(i<= S[0] && j<=T[0]){
        if(S[i] == T[j]){
            ++i;
            ++j;
        } //继续比较后继字符
        else{
            i = i-j+2;
            j = 1;
        }  //指针后退重新开始匹配
    } //while
    if(j>T[0])
        return i-T[0];
    else
        return 0;
}

Status StrAssign(SString T,char *chars)
{
    int i,ct;
    for(i = 0;i <= MAXSIZE; i++)
        T[i] = '\0';    //全部清零

    T[0] = strlen(chars);
    for(ct = 1;*chars != '\0';ct++,chars++){
        T[ct] = *chars;
    }
    return OK;
}

/*******************************主函数部分**************************************/

int main()
{
    SString S,T;
    char *chars1 = "abcdef";
    char *chars2 = "def";
    StrAssign(S,chars1);
    StrAssign(T,chars2);
    printf("S[0] = %d,T[0] = %d\n",S[0],T[0]);

    printf("子串T在主串S中第1个字符之后的位置 = %d.\n",Index(S,T,1));
    return 0;
}


