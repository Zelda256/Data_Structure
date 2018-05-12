#include <stdio.h>
#include <string.h>

char S[20]="ABCDEFGHIJK";
char T[5]="DEFG";
int next[5];
int pos=0;

/*******************************声明部分****************************************/
int index_KMP(char *s,char *t,int pos);
//利用模式串的t的next函数求t在主串s中的第pos个位置之后的位置的KMP算法（t非空，1<=pos<=Strlength(s)）。
void get_next(char * t,int * next);
//求模式串t的next函数的并存入数组next[]中。
/*******************************函数部分****************************************/
int index_KMP(char *s,char *t,int pos)
{
    int i=pos,j=1;

    while (i<=(int)strlen(s)&&j<=(int)strlen(t)){
        if (j==0  ||  s[i]==t[j-1]){ //继续进行后续字符串的比较
            i++;
            j++;
        }
        else
            j=next[j]; //模式串向右移动
   }
    if (j>(int)strlen(t)) //匹配成功
        return i-strlen(t)+1;
    else //匹配不成功
        return 0;
}

void get_next(char *t,int *next)
{
    int i=1,j=0;
    next[0]=next[1]=0;
    while (i<(int)strlen(t)) {
        if (j==0 || t[i]==t[j]){
            i++;
            j++;
            next[i]=j;
        } //if
      else
        j=next[j];
    } //while
}

/*******************************主函数部分**************************************/
int main()
{
    int n;
    get_next(T,next);
    n=index_KMP(S,T,pos);
    if(n!=0)
        printf("\n模式串T在主串S中第%d个位置\n\n",n);
    else
      printf("\n主串中不存在与模式串相匹配的子串!\n\n");
    return 0;
}
