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

// 6.15 是 6.14 的求精后的算法，只完成6.15
int A[4] = {0,1,2,3};  //前面的0不计算，只求第2-4个元素的幂集
int B[20];
int k = 0;
/*******************************声明部分****************************************/

void Output(int *B);
//输出当前B值
void GetPowerSet(int i,int n);
//求幂集

/*******************************函数部分****************************************/
void Output(int *B)
{
    int ct;
    printf("{");
    for(ct = 0;ct <k;ct++){
        printf(" %d ",B[ct]);
        if(ct != k-1)
            printf(",");
    }
    printf("},");

}

void GetPowerSet(int i,int n)
{
    int ct,B_len;
    if(i > n)
        Output(B);

    else{
        B[k] = A[i];
        k++;
        GetPowerSet(i+1,n);

        k--;
        GetPowerSet(i+1,n);
    }
}

/*******************************主函数部分**************************************/
int main()
{
    GetPowerSet(1,3);
    printf("\n");
    return 0;
}

