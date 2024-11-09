#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Node 
{
    int data;
    struct Node* link;
} node;


typedef struct stack 
{
    node* top;  // This acts as a head pointer to the data linked list 
    int size;  
} stk;


node* createNode(int data) 
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}


int is_empty(stk* sptr) 
{
    return sptr->top == NULL;
}


void push(stk* sptr, int data) 
{
    node* newNode = createNode(data);
    newNode->link = sptr->top;  
    sptr->top = newNode;        
    sptr->size++;
}


int pop(stk* sptr) 
{
    if (is_empty(sptr)) 
    {
        printf("Error: Stack Underflow\n");
        return INT_MIN;
    }
    int popped_val = sptr->top->data;
    node* temp = sptr->top;  

    sptr->top = sptr->top->link; 
    free(temp);  
    sptr->size--;

    return popped_val;
}


void display(stk* sptr) 
{
    if (is_empty(sptr)) 
    {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements are: ");
    node* temp = sptr->top;
    while (temp != NULL) 
    {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}


int main() 
{
    stk stack;
    stack.top = NULL; 
    stack.size = 0;

    int choice, value;
    while (1) 
    {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter the value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                display(&stack);
                break;
            case 2:
                value = pop(&stack);
                if (value != INT_MIN) 
                {
                    printf("Popped value: %d\n", value);
                }
                display(&stack);
                break;
            case 3:
                display(&stack);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
