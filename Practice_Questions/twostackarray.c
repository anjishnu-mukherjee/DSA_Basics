/*
Implement two stacks on the same array, managing space most efficiently.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct stack
{
    int a[MAX];
    int top1;
    int top2;
}twostack;

void initialise(twostack * s)
{
    s->top1 = -1;
    s->top2 = MAX;
}

void push1(twostack * s,int v)
{
    if(s->top1+1 < s->top2)
    {
        s->a[++(s->top1)]=v;
    }
    else
    {
        printf("Stack Overflow!\n");
    }
}

void push2(twostack * s, int v)
{
    if(s->top1+1 < s->top2)
    {
        s->a[--(s->top2)]=v;
    }
    else
    {
        printf("Stack Overflow!\n");
    }
}

int pop1(twostack * s)
{
    if (s->top1 == -1)
    {
        return INT_MIN;
    }
    else
    {
        return s->a[(s->top1)--];
    }
}

int pop2(twostack * s)
{
    if (s->top2 == MAX)
    {
        return INT_MIN;
    }
    else
    {
        return s->a[(s->top2)++];
    }
}

void print_stack(twostack * s)
{
    printf("Stack 1 : ");
    for ( int i = 0; i < s->top1; i++)
    {
        printf("%d ",s->a[i]);
    }
    printf("\nStack 2 : ");
    for ( int i = MAX; i >= s->top2; i--)
    {
        printf("%d ",s->a[i]);
    }
    printf("\n");
}

int main()
{
    twostack ts;
    initialise(&ts);

    push1(&ts, 10);
    push2(&ts, 100);
    push1(&ts, 20);
    push2(&ts, 200);
    push1(&ts, 30);

    print_stack(&ts);

    printf("Popped from Stack 1: %d\n", pop1(&ts));  // Output: 30
    printf("Popped from Stack 2: %d\n", pop2(&ts));  // Output: 200

    return 0;
}
