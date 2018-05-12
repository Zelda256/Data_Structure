#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40 //最大字符串
typedef int Status;
typedef char SString[MAXSIZE+1];
//此处声明的SString[maxsize+1]虽是数组，在SubString中作为指针使用，
//因位是指针，SString[0]存放实际数组的地址，使用时不用加*或&，直接传入数组的值
/*******************************声明部分****************************************/
Status StrAssign(SString T,char *chars);
//生成一个其值等于chars的串T  第一个元素为字符串长度
int StrLength(SString S);
//操作结果：返回S的元素个数，成为串的长度
int StrCompare(SString S,SString T);
//操作结果：若S>T，则返回值>0；若S = T，则返回值 =0；若S<T，则返回值<0
Status SubString(SString Sub, SString T,int pos,int len);
//用Sub返回串T的第pos个字符起长度为len的子串
int Index(SString S,SString T,int pos);
//若主串S中存在和串T值相同的子串，则返回它在主串中第pos个字符之后第一次出现的位置；否则函数值为0
/*******************************函数部分****************************************/
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

int StrLength(SString S)
{
    return S[0];
}

int StrCompare(SString S,SString T)
{
    int cnt = 1;
    while(cnt <= S[0] && cnt <= T[0]){   //非空前提下

        if(S[cnt] == T[cnt]){  //相等
            cnt++;
        }
        else{    //不相等
            return S[cnt] - T[cnt];
        }

    }
    return S[0]-T[0];
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

int Index(SString S,SString T,int pos)
{
    SString Sub;

    int i = pos;
    if(pos > 0){
        int n = StrLength(S),m = StrLength(T);

        while( i<= n-m+1){

            SubString(Sub,S,i,m-1);
            if(StrCompare(Sub,T)==0)
                return i;
            else
                i++;
            }
    }//if
    printf("不存在\n");
    return 0;  //S中不存在与T相等的子串
}//Index

/*******************************主函数部分**************************************/
int main()
{
    char *chars1 = "abcdefhg";
    char *chars2 = "defhg";
    SString S,T;

    StrAssign(S,chars1);
    StrAssign(T,chars2);

    int ANSWER = Index(S,T,1);
    printf("找到子串T在S中的位置 = %d\n",ANSWER);
    return 0;
}
