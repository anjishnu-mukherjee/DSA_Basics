#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct 
{
    char arr[MAX];
    int top;
} Stack;


void initStack(Stack *s) 
{
    s->top = -1;
}


bool isEmpty(Stack *s) 
{
    return s->top == -1;
}


bool isFull(Stack *s)
{
    return s->top == MAX - 1;
}


void push(Stack *s, char ch) 
{
    if (!isFull(s)) 
    {
        s->arr[++(s->top)] = ch;
    }
}


char pop(Stack *s) 
{
    if (!isEmpty(s)) 
    {
        return s->arr[(s->top)--];
    }
    return '\0'; 
}


bool isBalanced(const char *expr) 
{
    Stack s;
    initStack(&s);

    for (int i = 0; expr[i] != '\0'; i++) 
    {
        if (expr[i] == '(') 
        {
            push(&s, '(');
        } else if (expr[i] == ')') 
        {
            if (isEmpty(&s)) 
            {
                return false; 
            }
            pop(&s);
        }
    }

    return isEmpty(&s);  
}


int main() 
{
    char expr[MAX];

    printf("Enter a sequence of parentheses: ");
    scanf("%s", expr);

    if (isBalanced(expr)) {
        printf("The sequence is balanced.\n");
    } else {
        printf("The sequence is not balanced.\n");
    }

    return 0;
}