#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

typedef struct stack
{
    int top;
    int capacity;
    char* datastk;
} stk;


void allocate(stk* sptr, int size)
{
    sptr->top = -1;
    sptr->capacity = size;
    sptr->datastk = (char*)malloc(sizeof(char) * size); // Allocate memory for datastk
}


void push(stk* sptr, char data_val)
{
    if (sptr->top < sptr->capacity - 1)
    {
        sptr->top++;
        sptr->datastk[sptr->top] = data_val;
    }
    else
    {
        printf("Stack overflow\n");
    }
}


char pop(stk* sptr)
{
    if (sptr->top >= 0)
    {
        char c = sptr->datastk[sptr->top];
        sptr->top--;
        return c;
    }
    else
    {
        printf("Stack underflow\n");
        return '\0';
    }
}


int emptystk(stk* sptr)
{
    return (sptr->top == -1);
}


int precedence(char c)
{
    if (c == '^')
    {
        return 4;
    }
    else if (c == '%')
    {
        return 3;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else if (c == '-' || c == '+')
    {
        return 1;
    }
    else if (c == '(')
    {
        return 0;
    }
    return INT_MIN;
}


char associativity(char c)
{
    if (c == '^')
    {
        return 'R';
    }
    else
    {
        return 'L';
    }
}


char* infix_to_postfix(char* infix, stk* sptr)
{
    int len = strlen(infix);
    char c, top, x;
    int i;
    char* postfix = (char*)malloc(sizeof(char) * len);
    int j = 0;
    allocate(sptr, len);
    for (i = 0; i < len; i++)
    {
        c = infix[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        {
            postfix[j] = c;
            j++;
        }
        else if (c == '(')
        {
            push(sptr, c);
        }
        else if (c == ')')
        {
            while (!emptystk(sptr) && (top = pop(sptr)) != '(')
            {
                postfix[j] = top;
                j++;
            }
            if (top != '(')
            {
                printf("\nError in infix expression\n");
                return NULL;
            }
        }
        else
        {
            while (!emptystk(sptr))
            {
                top = pop(sptr);
                if ((precedence(c) < precedence(top)) || ((precedence(c) == precedence(top) && associativity(top) == 'L')))
                {
                    postfix[j] = top;
                    j++;
                }
                else
                {
                    push(sptr, top);
                    break;
                }
            }
            push(sptr, c);
        }
    }


    while (!emptystk(sptr))
    {
        x = pop(sptr);
        postfix[j] = x;
        j++;
    }
    postfix[j] = '\0';
    return postfix;
}


typedef struct int_stack
{
    int top;
    int size_capacity;
    float* dataStk;
} int_stk;


void allocate_int_stack(int_stk* sptr, int size)
{
    sptr->top = -1;
    sptr->size_capacity = size;
    sptr->dataStk = (float*)malloc(sizeof(float) * size);
}


void push_int(int_stk* sptr, float data_val)
{
    if (sptr->top < sptr->size_capacity - 1)
    {
        sptr->top++;
        sptr->dataStk[sptr->top] = data_val;
    }
    else
    {
        printf("Operand stack overflow\n");
    }
}


float pop_int(int_stk* sptr)
{
    if (sptr->top >= 0)
    {
        float val = sptr->dataStk[sptr->top];
        sptr->top--;
        return val;
    }
    else
    {
        printf("Operand stack underflow\n");
        return 0;
    }
}


int is_empty_int_stack(int_stk* sptr)
{
    return (sptr->top == -1);
}


float evaluate_postfix_expr(char* postfix, int_stk* operand_stk_ptr)
{
    int i = 0;
    char c;
    float operand1, operand2, value;
    float variables[26] = {0}; // To store values of variables (a-z)
    int is_var_set[26] = {0}; // To track if variable values have been set


    while (postfix[i] != '\0')
    {
        c = postfix[i];

        
        if (isalpha(c))
        {
            if (!is_var_set[c - 'a']) // If variable value has not been set yet
            {
                printf("Enter value for %c: ", c);
                scanf("%f", &value);
                variables[c - 'a'] = value; // Store value in array
                is_var_set[c - 'a'] = 1;    // Mark the variable as set
            }
            push_int(operand_stk_ptr, variables[c - 'a']); // Push the variable's value onto the operand stack
        }
        // If the character is a digit, handle multi-digit numbers if needed
        else if (isdigit(c))
        {
            push_int(operand_stk_ptr, c - '0'); // Convert char to int and push
        }
        else
        {
            operand2 = pop_int(operand_stk_ptr); // Second operand (popped first)
            operand1 = pop_int(operand_stk_ptr); // First operand (popped second)


            switch (c)
            {
                case '+':
                    push_int(operand_stk_ptr, operand1 + operand2);
                    break;
                case '-':
                    push_int(operand_stk_ptr, operand1 - operand2);
                    break;
                case '*':
                    push_int(operand_stk_ptr, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 != 0)
                    {
                        push_int(operand_stk_ptr, operand1 / operand2);
                    }
                    else
                    {
                        printf("Division by zero error\n");
                        return 0;
                    }
                    break;
                case '^':
                    push_int(operand_stk_ptr, pow(operand1, operand2));
                    break;
                default:
                    printf("Invalid operator encountered: %c\n", c);
                    return 0;
            }
        }
        i++;
    }
    return pop_int(operand_stk_ptr); // The final result will be the last value in the stack
}


int main()
{
    int n;
    printf("\nEnter the length of infix expression: ");
    scanf("%d", &n);
    char* infix = (char*)malloc(sizeof(char) * n);
    printf("\nEnter the expression: ");
    scanf("%s", infix);


    // Create stack for infix to postfix conversion
    stk s;
    allocate(&s, n);


    // Convert to postfix
    char* postfix = infix_to_postfix(infix, &s);
    if (postfix != NULL)
    {
        printf("\nPostfix Expression: %s\n", postfix);


        // Evaluate the postfix expression
        int_stk operand_stk;
        allocate_int_stack(&operand_stk, n);


        float result = evaluate_postfix_expr(postfix, &operand_stk);
        printf("\nEvaluated Result: %.2f\n", result);
    }


    return 0;
}