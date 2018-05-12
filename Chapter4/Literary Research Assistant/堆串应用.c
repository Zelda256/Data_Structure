#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef int Status;
typedef int ElemType; //定义链表的数据元素类型为整型
typedef int Boolean;

typedef struct
{
    char *ch;  //如果是非空串，则按串长分配存储区，否则ch为NULL
    int length;  //串长度
}HString;
#define MaxLen 500  //最大长度(500)
char buf[MaxLen];  //缓冲区
int next[5];
int pos=0;

/*******************************声明部分****************************************/

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

void GetLine(FILE *f)
{
    fgets(buf,MaxLen,f);
}

void ShowFile(FILE *FileName)
{
    printf("文件内容：\n");
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

void InputFile(FILE *FileName)
{
    printf("写入文件（Ctrl+Z完成输入）:\n");
    char s[MaxLen];
    char ch;
    FILE *g;
    if((g = fopen("writefile.txt","w")) == NULL){
        printf("ERROR in open the file.txt\n");
        exit(1);
    }
    while((ch = getchar()) != EOF)
        fprintf(g,"%c",ch);

    fclose(g);
}

void SearchWordInFile(FILE *FileName)
{
    FILE *f;
    int row_loc,col_Loc;
    if((f = fopen("readfile.txt","r")) == NULL){
        printf("ERROR in open the readfile.txt\n");
        exit(1);
    }
    ShowFile(f);
    char SearchWord[20];
    printf("输入要查找的单词：\n");
    scanf("%s",&SearchWord);
    row_loc = 0;
    while(!feof(f)){
        GetLine(f);   //读取文件中的一行到缓冲区
        row_loc++;
        if((col_Loc = index_KMP(buf,SearchWord,pos)) != 0){
            printf("找到，在第%d行，第%d个位置\n",row_loc,col_Loc);
            return;
        }
    }
    printf("对不起，找不到。\n");
}

/*******************************主函数部分**************************************/

int main()
{
    FILE *f,*g;
    if((f = fopen("readfile.txt","r")) == NULL){
        printf("ERROR in open the readfile.txt\n");
        exit(1);
    }
    if((g = fopen("writefile.txt","r")) == NULL){
        printf("ERROR in open the writefile.txt\n");
        exit(1);
    }
    int choice = -1;
    printf("请选择：\n 1.读取readfile文件\n 2.新建一个writefile文件\n 3.查找一个单词\n 0.退出\n");
    while(choice != 0){
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            ShowFile(f);
            printf("\n");
            break;
        case 2:
            InputFile(g);
            ShowFile(g);
            printf("\n");
            break;
        case 3:
            SearchWordInFile(f);
            printf("\n");
            break;
        case 0:
            break;
        default:
            printf("没有该选项，请重新输入\n");
            printf("\n");

        }
    if(choice != 0)
        printf("请选择：\n 1.读取readfile文件\n 2.新建一个writefile文件\n 3.查找一个单词\n 0.退出\n");
    }
    fclose(f);
    fclose(g);
    printf("任意键结束...\n");
    _getch();

    return 0;
}
