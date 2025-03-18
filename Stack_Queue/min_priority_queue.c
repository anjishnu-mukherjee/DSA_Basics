#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100

typedef struct
{
    int heap[SIZE];
    int size;
} MinPriorityQueue;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinPriorityQueue *pq, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < pq->size && pq->heap[left] < pq->heap[smallest])
    {
        smallest = left;
    }

    if (right < pq->size && pq->heap[right] < pq->heap[smallest])
    {
        smallest = right;
    }

    if (smallest != i)
    {
        swap(&pq->heap[i], &pq->heap[smallest]);
        min_heapify(pq, smallest);
    }
}

void enqueue(MinPriorityQueue *pq, int key)
{
    if (pq->size == SIZE)
    {
        printf("Queue Overflow!\n");
        return;
    }

    int i = pq->size;
    pq->heap[i] = key;
    pq->size++;

    while (i > 0 && pq->heap[(i - 1) / 2] > pq->heap[i])
    {
        swap(&pq->heap[i], &pq->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int dequeue(MinPriorityQueue *pq)
{
    if (pq->size <= 0)
    {
        printf("Queue Underflow!\n");
        return INT_MIN;
    }

    int root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    min_heapify(pq, 0);
    return root;
}

void heap_decrease_key(MinPriorityQueue *pq, int index, int newkey)
{
    if (index >= pq->size || newkey > pq->heap[index])
    {
        printf("Invalid Decrease Operation!\n");
        return;
    }

    pq->heap[index] = newkey;

    while (index > 0 && pq->heap[(index - 1) / 2] > pq->heap[index])
    {
        swap(&pq->heap[index], &pq->heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void display(MinPriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("Priority Queue is Empty!\n");
        return;
    }

    printf("Priority Queue: ");
    for (int i = 0; i < pq->size; i++)
    {
        printf("%d ", pq->heap[i]);
    }
    printf("\n");
}

int main()
{
    MinPriorityQueue pq;
    pq.size = 0;
    int choice, value, index, newValue;

    while (1)
    {
        printf("\nPriority Queue Operations:\n");
        printf("1. Enqueue (Insert)\n");
        printf("2. Dequeue (Extract Min)\n");
        printf("3. Display\n");
        printf("4. Decrease Key\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            enqueue(&pq, value);
            break;
        case 2:
            value = dequeue(&pq);
            if (value != INT_MAX)
                printf("Extracted Min: %d\n", value);
            break;
        case 3:
            display(&pq);
            break;
        case 4:
            printf("Enter index and new key value: ");
            scanf("%d %d", &index, &newValue);
            heap_decrease_key(&pq, index, newValue);
            break;
        case 5:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
