#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct cll {
    int data;
    struct cll *link;
} cnode;

typedef struct queuecll {
    cnode *front;
    cnode *rear;
    int size;
} c_queue;

void cll_insert_at_end(cnode **tptr, int val) 
{
    cnode *new_node = (cnode *)malloc(sizeof(cnode));
    new_node->data = val;
    if (*tptr == NULL) 
    {
        *tptr = new_node;
        new_node->link = new_node;
    } else 
    {
        new_node->link = (*tptr)->link;
        (*tptr)->link = new_node;
        *tptr = new_node;
    }
}

int cll_delete_at_beg(cnode **tptr) 
{
    if (*tptr == NULL) 
    {
        printf("List is Empty\n");
        return INT_MIN;
    }
    cnode *curr = (*tptr)->link;
    int del_data = curr->data;

    if (*tptr == curr) 
    {
        *tptr = NULL;
    } else 
    {
        (*tptr)->link = curr->link;
    }

    free(curr);
    return del_data;
}

void cll_print(cnode **tptr) 
{
    if (*tptr == NULL) 
    {
        printf("NULL\n");
    } else 
    {
        cnode *curr = (*tptr)->link;
        do 
        {
            printf("%d -> ", curr->data);
            curr = curr->link;
        } while (curr != (*tptr)->link);

        printf("NULL\n");
    }
}

int is_empty(c_queue *qptr) 
{
    return qptr->front == NULL;
}

void enqueue(c_queue *q, int val) 
{
    cll_insert_at_end(&q->rear, val);
    if (q->front == NULL) 
    {
        q->front = q->rear;
    }
    q->size++;
}

void dequeue(c_queue *q) 
{
    if (is_empty(q)) 
    {
        printf("Queue is empty\n");
        return;
    }
    int del_data = cll_delete_at_beg(&q->rear);
    if (del_data != INT_MIN) 
    {
        printf("Dequeued: %d\n", del_data);
        if (q->rear == NULL) 
        {
            q->front = NULL;
        }
        q->size--;
    }
}

void display_queue(c_queue *q) 
{
    if (is_empty(q)) 
    {
        return;
    } 
    else 
    {
        printf("Queue: ");
        cll_print(&q->rear);
    }
}

int main() 
{
    c_queue q;
    q.front = NULL;
    q.rear = NULL;
    q.size = 0;

    int choice, value;

    while(1)
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
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                display_queue(&q);
                break;
            case 2:
                dequeue(&q);
                display_queue(&q);
                break;
            case 3:
                display_queue(&q);
                break;
            case 4:
                printf("Exiting...\n");
                exit(1);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
