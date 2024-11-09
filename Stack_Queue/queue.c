#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct 
{
    int front;
    int rear;
    int *arr;
    int capacity;
}queue;

void allocate(queue* q,int n)
{
    q->capacity=n;
    q->front=-1;
    q->rear=-1;
    q->arr = (int*)malloc(sizeof(int)*n);
}

int isFull(queue* q)
{
    return ((q->rear+1)%q->capacity == q->front);
}

int isEmpty(queue* q)
{
    return (q->front == -1);
}

void enqueue(queue* q,int val)
{
    if (isFull(q))
    {
        printf("Queue Overflow!\n");
        return;
    }
    if (q->front == -1) 
    {
        q->front = 0;
    }
    q->rear = (q->rear + 1)%(q->capacity);
    q->arr[q->rear] = val;
}

int dequeue(queue* q)
{
    if (isEmpty(q))
    {
        printf("Queue Underflow!\n");
        return INT_MIN;
    }

    int del_val = q->arr[q->front];

    if (q->front == q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1)%(q->capacity);
    }
    return del_val;
}

void display(queue* q)
{
    if (isEmpty(q))
    {
        return;
    }
    else
    {
        printf("Queue elements: ");
        int i = q->front;
        while (i != q->rear)
        {
            printf("%d ", q->arr[i]);
            i = (i + 1) % q->capacity;
        }
        printf("%d ", q->arr[q->rear]);  
        printf("\n");
    }
}


int main()
{
    queue q;
    int capacity, choice, value, dequeued_val;

    printf("Enter the size of the queue: ");
    scanf("%d", &capacity);

    allocate(&q, capacity);

    do
    {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
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
                dequeued_val = dequeue(&q);
                if (dequeued_val != INT_MIN)
                {
                    printf("%d dequeued from the queue.\n", dequeued_val);
                }
                display(&q);
                break;

            case 3:
                display(&q);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    } while (choice != 4);

    free(q.arr); 
    return 0;
}