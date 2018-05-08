#include<stdio.h>
#include<malloc.h>
#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define BUFFERSIZE 256

typedef int Status;
typedef int opndElem;
typedef struct{
    opndElem *base;
    opndElem *top;
    int stacksize;
}OpndStack;

typedef char optrElem;
typedef struct{
    optrElem *base;
    optrElem *top;
    int stacksize;
}OptrStack;
