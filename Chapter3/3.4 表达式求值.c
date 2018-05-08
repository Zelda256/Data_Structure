#include<stdio.h>
#include<malloc.h>
#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define BUFFERSIZE 256

typedef int Status; //函数返回状态
typedef int opndElem;  //操作数元素类型
typedef struct{//操作数栈结构定义
    opndElem *base;
    opndElem *top;
    int stacksize;
}OpndStack;

typedef char optrElem;//操作符元素类型
typedef struct{//操作符栈结构定义
    optrElem *base;
    optrElem *top;
    int stacksize;
}OptrStack;
/*******************************声明部分****************************************/
//==========操作数栈=============//
Status InitStack_OPND(OpndStack *S);
    //构造一个空栈S
Status GetTop_OPND(OpndStack S,opndElem *e);
    //若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
Status Push_OPND(OpndStack *S,opndElem e);
    //插入元素e为新的栈顶元素
Status Pop_OPND(OpndStack *S,opndElem *e);
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR

//==========操作符栈=============//
Status InitStack_OPTR(OptrStack *S);
    //构造一个空栈S
optrElem GetTop_OPTR(OptrStack S);
    //若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
Status Push_OPTR(OptrStack *S,optrElem e);
    //插入元素e为新的栈顶元素
Status Pop_OPTR(OptrStack *S,optrElem *e);
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR

//============运算操作================//
void Standard(char *expression);
    //将表达式标准化
opndElem EvalueateExpression(const char *expression);
    //算数表达式求值
Status Isoperator(char c);
    //判断c是否是一个操作符
char Precede(char op1,char op2);
    //判断op1和op2优先级的高低，返回'>','<','='
opndElem operate(opndElem a,optrElem theta,opndElem b);
    //对操作数a，b进行theta运算
const char *getOpnd(const char *c,opndElem *op);
    //获得以*c开始的操作数，返回后c为操作符
/*******************************函数部分****************************************/
//==========操作数栈===========//
Status InitStack_OPND(OpndStack *S){
    //构造一个空操作数栈S
    S->base=(opndElem *)malloc(STACK_INIT_SIZE*sizeof(opndElem));
    if(!S->base)//分配失败
    {
        printf("分配内存失败.\n");
        exit(0);
    }
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

Status GetTop_OPND(OpndStack S,opndElem *e){
    //若操作数栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
    if(S.top==S.base){
        printf("栈为空.\n");
        return FALSE;
    }else{
        *e=*(S.top-1);
        return OK;
    }
}

Status Push_OPND(OpndStack *S,opndElem e){
    //插入元素e为新的栈顶元素
    if(S->top-S->base>=S->stacksize){//栈已满，追加存储空间
        S->base=(opndElem *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(opndElem));
        if(!S->base)
        {
            printf("重新申请空间失败.\n");
            exit(0);
        }
        S->top=S->base+S->stacksize;//更改栈顶指针
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

Status Pop_OPND(OpndStack *S,opndElem *e){
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR
    if(S->top==S->base){//栈为空
        printf("栈为空.\n");
        return ERROR;
    }
    *e=*(--S->top);
    return OK;
}

//==========操作符栈===========//
Status InitStack_OPTR(OptrStack *S){
    //构造一个空操作数栈S
    S->base=(optrElem *)malloc(STACK_INIT_SIZE*sizeof(optrElem));
    if(!S->base)//分配失败
    {
        printf("分配内存失败.\n");
        exit(0);
    }
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}

optrElem GetTop_OPTR(OptrStack S){
    //若操作数栈不为空，则返回S的栈顶元素，并返回OK；否则返回FALSE
    optrElem e;
    if(S.top==S.base){
        printf("栈为空.\n");
    }else{
        e=*(S.top-1);
    }
    return e;
}

Status Push_OPTR(OptrStack *S,optrElem e){
    //插入元素e为新的栈顶元素
    if(S->top-S->base>=S->stacksize){//栈已满，追加存储空间
        S->base=(optrElem *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(optrElem));
        if(!S->base)
            exit(0);
        S->top=S->base+S->stacksize;//更改栈顶指针
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}

Status Pop_OPTR(OptrStack *S,optrElem *e){
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR
    if(S->top==S->base){//栈为空
        printf("栈为空.\n");
        return ERROR;
    }
    *e=*(--S->top);
    return OK;
}

//============运算操作================//
opndElem EvalueateExpression(const char *expression){
    //对只有四则运算符的算数表达式 expression 求值
    //OPTR:操作符栈，OPND:操作数栈
    const char *c=expression;
    OpndStack OPND;
    OptrStack OPTR;
    optrElem x,theta;
    opndElem a,b,num,result;
    InitStack_OPTR(&OPTR);
    InitStack_OPND(&OPND);
    Push_OPTR(&OPTR,'#');    //首先将匹配符号'#'入栈
    while(*c!='#'||GetTop_OPTR(OPTR)!='#'){
        //printf("getchar=%c\n",*c);
        if(*c=='\0')
            break;
        if(FALSE==Isoperator(*c)){
            c=getOpnd(c,&num);
            Push_OPND(&OPND,num);
        }
        else
            switch(Precede(GetTop_OPTR(OPTR),*c)){
                case '<':
                    Push_OPTR(&OPTR,*c);
                    c++;
                    break;
                case '=':
                    Pop_OPTR(&OPTR,&x);
                    c++;
                    break;
                case '>':
                    Pop_OPTR(&OPTR,&theta);
                    Pop_OPND(&OPND,&b);
                    Pop_OPND(&OPND,&a);
                    result=operate(a,theta,b);
                    Push_OPND(&OPND,result);
                    break;
                default:
                    break;
            }//switch
    }//while
    GetTop_OPND(OPND,&result);
    return result;
}

void Standard(char *expression){
    //将字符串表达式标准化为算术表达式
    char *p=expression,*q;
    while(*p!='\0'){   //遍历字符串
        if(*p==' '){    //如果是空格，删除
            q=p;
            do{
                *q=*(q+1);
                q++;
            }while(*q!='\0');
        }
        p++;
    }
    *p++='#';
    *p='\0';
}

const char *getOpnd(const char *c,opndElem *op){
    //获得以*c开始的操作数，返回后c为操作符
    int sum=0,tmp;
    while(FALSE==Isoperator(*c)){//当c不是操作符
        tmp=*c-'0';
        sum=sum*10+tmp;
        //printf("tmp=%d\n",tmp);
        c++;
    }
    *op=sum;
    //printf("getOpnd:%d\n",*op);
    return c;
}

Status Isoperator(char c){
    //判断c是否是一个运算操作符
    switch(c){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '#':
            return TRUE;
            break;
        default:
            return FALSE;
            break;
    }
}

char Precede(char op1,char op2){
    //判断op1和op2优先级的高低，返回'>','<','='
    switch(op1){
        case '+':
            switch(op2){
                case '*':
                case '/':
                case '(':
                       return '<';
                       break;
                default:
                    return '>';
                    break;
            }
            break;
        case '-':
            switch(op2){
                case '*':
                case '/':
                case '(':
                       return '<';
                       break;
                default:
                    return '>';
                    break;
            }
            break;
        case '*':
            switch(op2){
                case '(':
                       return '<';
                       break;
                default:
                    return '>';
                    break;
            }
            break;
        case '/':
            switch(op2){
                case '(':
                       return '<';
                       break;
                default:
                    return '>';
                    break;
            }
            break;
        case '(':
            switch(op2){
                case ')':
                    return '=';
                    break;
                default:
                    return '<';
                    break;
            }
            break;
        case ')':
            switch(op2){
                default:
                    return '>';
                    break;
            }
            break;
        case '#':
            switch(op2){
                case '#':
                    return '=';
                    break;
                default:
                    return '<';
                    break;
            }
            break;
        default:
            return '<';
            break;
    }
}

opndElem operate(opndElem a,optrElem theta,opndElem b){
    //对操作数a，b进行theta运算，并返回运算结果
    //theta只能是四则运算符号
    int rs_i;
    switch(theta){
        case '+':
            rs_i=a+b;
            break;
        case '-':
            rs_i=a-b;
            break;
        case '*':
            rs_i=a*b;
            break;
        case '/':
            if(b==0){
                printf("errror:除数为0.");
                exit(0);
            }
            rs_i=a/b;
            break;
        default:
            printf("Is not a operator.\n");
            break;
    }
    printf("%d %c %d = %d\n",a,theta,b,rs_i);
    return rs_i;

}

/*******************************主函数部分**************************************/
int main()
{
    opndElem result=0;
    char *expression=(char*)malloc(sizeof(char)*BUFFERSIZE);
    if(expression==NULL)
        exit(0);

    printf("Please enter an expression(for example 4+2*3-10/5):\n");
    gets(expression);
    Standard(expression);
    result=EvalueateExpression(expression);
    printf("The result is  %d\n",result);
    return 0;
}
