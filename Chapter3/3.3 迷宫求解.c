#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100  //存储空间初始分配量
#define STACKINCREMENT 10  //存储空间分配增量
typedef int Status;
typedef struct
{
    int row;
    int col;
}PosType;
typedef struct
{
    int ord;  //通道块在路劲上的“序号”
    PosType seat;  //通道块在迷宫中的“坐标位置”
    int di;  //从此通道块走向下一通道块的“方向”
}SElemType;

typedef struct
{
    SElemType *base;  //在栈构造之前和销毁之后，base的值为NULL
    SElemType *top;  //栈顶指针
    int stacksize;  //当前已分配的存储空间，以元素为单位
}SqStack;

int MazeMap[10][10] =    //迷宫地图为全局变量
{
   //0,1,2,3,4,5,6,7,8,9
    {0,0,0,0,0,0,0,0,0,0}, //0
    {0,1,1,0,1,1,1,0,1,0}, //1
    {0,1,1,0,1,1,1,0,1,0}, //2
    {0,1,1,1,1,0,0,1,1,0}, //3
    {0,1,0,0,0,1,1,1,1,0}, //4
    {0,1,1,1,0,1,1,1,1,0}, //5
    {0,1,0,1,1,1,0,1,1,0}, //6
    {0,1,0,0,0,1,0,0,1,0}, //7
    {0,0,1,1,1,1,1,1,1,0}, //8
    {0,0,0,0,0,0,0,0,0,0}  //9
};
//***************注意在数组中与坐标的不同表示方法，容易混淆

/*******************************声明部分****************************************/

/*******************************函数部分****************************************/
Status InitStack(SqStack *S)
{
    (*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!(*S).base)
        exit(OVERFLOW);

    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack *S,SElemType e)
{
    *(*S).top++ = e;
    return OK;
}

Status Pop(SqStack *S,SElemType *e)
{
    if((*S).top == (*S).base)
        return ERROR;
    *e = *(--(*S).top);
    return OK;
}

Status StackEmpty(SqStack S)
{
    if(S.top==S.base)
        return OK;
    return ERROR;
}

void PrintMaze( )
{
    printf("\n 迷宫的地图为：\n\n");
    int i,j;
    for(i = 0;i<10;i++){
        for(j = 0;j<10;j++)
            printf(" %3d",MazeMap[i][j]);
        printf("\n");
    }
}

Status FootPrint(PosType pos,int curstep)
{
    MazeMap[pos.row][pos.col] = curstep;
}

Status Pass(PosType pos)
{
    if(MazeMap[pos.row][pos.col] == 1)
        return TRUE;

    return FALSE;
}

PosType NextPos(PosType CurPos,int i)
{
    switch(i)
    {
    case 1:
        ++CurPos.row;  //东
            break;
    case 2:
        ++CurPos.col;  //南
            break;
    case 3:
        --CurPos.row;  //西
            break;
    case 4:
        --CurPos.col; //北

            break;
    }//switch
    return CurPos;
}

void MakePrint(PosType pos)
{
    printf("(%d,%d)走不通\n",pos.row,pos.col);
    MazeMap[pos.row][pos.col] = 0;  //将走不通的块替换为墙壁
}

Status MazePath(PosType start,PosType end)
{
    SqStack S;
    PosType curpos;
    SElemType e;
    int curstep;

    InitStack(&S);
    curpos = start; //设定“当前位置”为“入口位置”
    curstep = 1; //探索第一步
    printf("起点：(%d,%d)",start.row,start.col);
    do{
        if(Pass(curpos)){  //当前位置可以通过，即使未曾走到过的通道块
            FootPrint(curpos,curstep);  //留下足迹
            printf("  ->(%3d,%3d)\n",curpos.row,curpos.col);
            e.ord = curstep;
            e.seat = curpos;
            e.di = 1;
            Push(&S,e);  //加入路径

            if(curpos.row == end.row && curpos.col == end.col){  //到达终点
                printf("到达终点：(%3d,%3d)\n",e.seat.col,e.seat.row);
                return TRUE;
            }
            curpos = NextPos(curpos,1);   //下一位置是当前位置的东邻
            curstep++;  //探索下一步
            printf("step:%d",curstep);
        }//if
        else{  //当前位置不能通过
            if(!StackEmpty(S)){

                Pop(&S,&e);
                while(e.di == 4 && !StackEmpty(S)){
                    MakePrint(e.seat);
                    Pop(&S,&e);
                    curstep--;
                    printf("倒退到(%3d,%3d)\n",e.seat.col,e.seat.row);
                }//while
                if(e.di < 4){
                    ++e.di;  //换下一个方向探索
                    Push(&S,e);
                    curpos = NextPos(e.seat,e.di); //设定当前位置是该新方向上的相邻块
                }//if
            }//if
        }//else
    }while(!StackEmpty(S));
    printf("对不起，找不到出口\n");
    return FALSE;
}


/*******************************主函数部分**************************************/

int main()
{
    PrintMaze();
    PosType Start,End;
    Start.col = 1;
    Start.row = 1;
    End.col = 8;
    End.row = 8;
    MazePath(Start,End);
    PrintMaze();
    return 0;
}


