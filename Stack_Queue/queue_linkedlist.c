#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Node {
    int data;
    struct Node* link;
} node;


typedef struct {
    node* front;  
    node* rear;   
    int size;     
} queue;


node* createNode(int data) 
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}


int is_empty(queue* qptr) 
{
    return qptr->front == NULL;
}


void enqueue(queue* qptr, int data) 
{
    node* newNode = createNode(data);
    if (is_empty(qptr)) 
    {
        qptr->front = newNode;
        qptr->rear = newNode;
    } 
    else 
    {
        qptr->rear->link = newNode;
        qptr->rear = newNode;        
    }
    qptr->size++;
    printf("Enqueued %d to the queue.\n", data);
}


int dequeue(queue* qptr) 
{
    if (is_empty(qptr)) 
    {
        printf("Error: Queue Underflow\n");
        return INT_MIN;
    }
    node* temp = qptr->front;  
    int dequeued_val = temp->data;
    qptr->front = qptr->front->link;  
    free(temp);  
    qptr->size--;

   
    if (qptr->front == NULL) 
    {
        qptr->rear = NULL;
    }
    return dequeued_val;
}


void display(queue* qptr) 
{
    if (is_empty(qptr)) 
    {
        printf("Queue is empty.\n");
        return;
    }
    node* temp = qptr->front;
    printf("Queue elements are: ");
    while (temp != NULL) 
    {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}


int main() 
{
    queue q;
    q.front = NULL;  
    q.rear = NULL;
    q.size = 0;

    int choice, value;
    while (1) 
    {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter the value to enqueue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                display(&q);
                break;
            case 2:
                value = dequeue(&q);
                if (value != INT_MIN) 
                {
                    printf("Dequeued value: %d\n", value);
                }
                display(&q);
                break;
            case 3:
                display(&q);
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
