#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct stack 
{
    int* dataarr;
    int capacity;
    int top;
} stk;


void allocate_stack(stk* sptr, int capacity) 
{
    sptr->capacity = capacity;
    sptr->top = -1;
    sptr->dataarr = (int*)malloc(sptr->capacity * sizeof(int));
}


int is_empty(stk* sptr) 
{
    return sptr->top == -1;
}


int is_full(stk* sptr) 
{
    return sptr->top == (sptr->capacity - 1);
}


int push(stk* sptr, int val) 
{
    if (is_full(sptr)) 
    {
        printf("Error: Stack Overflow\n");
        return 0;
    }
    sptr->top = sptr->top + 1;
    sptr->dataarr[sptr->top] = val;
    return 1;
}


int pop(stk* sptr) 
{
    if (is_empty(sptr)) 
    {
        printf("Error: Stack Underflow\n");
        return 0;
    }
    int popped_val = sptr->dataarr[sptr->top];
    sptr->top = sptr->top - 1;
    return popped_val;
}


void print_stack(stk* sptr) 
{
    if (is_empty(sptr)) 
    {
        printf("Stack is empty.\n");
        return;
    }
    for (int i = 0; i <= sptr->top; i++) 
    {
        printf("%d ", sptr->dataarr[i]);
    }
    printf("\n");
}



int main() 
{
    stk stack;
    int choice, value, capacity;

    printf("Enter the stack capacity: ");
    scanf("%d", &capacity);

    allocate_stack(&stack, capacity);

    while (1) 
    {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Print Stack\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                print_stack(&stack);
                break;
            case 2:
                value = pop(&stack);
                if (value != 0) 
                {
                    printf("Popped value: %d\n", value);
                }
                print_stack(&stack);
                break;
            case 3:
                print_stack(&stack);
                break;
            case 4:
                free(stack.dataarr);
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
