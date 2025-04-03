#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100
#define INF INT_MAX

typedef struct
{
    int parent;
    int key;
    int idx;
} queue;

typedef struct
{
    int adj;
    int wt;
} node;

typedef struct
{
    int deg;
    node *arr;
} vertex;

typedef struct
{
    int numVertex;
    vertex *g;
} Graph;

Graph *readGraph(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("Error opening file");
        return NULL;
    }

    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
    {
        fclose(fp);
        return NULL;
    }

    fscanf(fp, "%d", &(graph->numVertex));
    int V = graph->numVertex;
    graph->g = (vertex *)malloc(V * sizeof(vertex));
    if (!graph->g)
    {
        free(graph);
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < V; i++)
    {
        int id, deg;
        fscanf(fp, "%d %d", &id, &deg);
        graph->g[id].deg = deg;
        graph->g[id].arr = (node *)malloc(deg * sizeof(node));
        for (int j = 0; j < deg; j++)
        {
            fscanf(fp, "%d %d", &(graph->g[id].arr[j].adj), &(graph->g[id].arr[j].wt));
        }
    }
    fclose(fp);
    return graph;
}

void printGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertex; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < graph->g[i].deg; j++)
        {
            printf("%d[%d] ", graph->g[i].arr[j].adj, graph->g[i].arr[j].wt);
        }
        printf("\n");
    }
    printf("\n");
}

void freeGraph(Graph *graph)
{
    if (graph)
    {
        for (int i = 0; i < graph->numVertex; i++)
        {
            free(graph->g[i].arr);
        }
        free(graph->g);
        free(graph);
    }
}

// Min Priority Queue based on my lab implementation
typedef struct
{
    queue heap[SIZE];
    int size;
} MinPQ;

void swapQueue(queue *a, queue *b)
{
    queue temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinPQ *pq, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < pq->size && pq->heap[left].key < pq->heap[smallest].key)
        smallest = left;
    if (right < pq->size && pq->heap[right].key < pq->heap[smallest].key)
        smallest = right;
    if (smallest != i)
    {
        swapQueue(&pq->heap[i], &pq->heap[smallest]);
        min_heapify(pq, smallest);
    }
}

void insertMinPQ(MinPQ *pq, queue element)
{
    if (pq->size >= SIZE)
    {
        printf("Priority Queue Overflow!\n");
        return;
    }
    int i = pq->size;
    pq->heap[i] = element;
    pq->size++;
    while (i > 0 && pq->heap[(i - 1) / 2].key > pq->heap[i].key)
    {
        swapQueue(&pq->heap[i], &pq->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

queue extractMin(MinPQ *pq)
{
    if (pq->size <= 0)
    {
        printf("Priority Queue Underflow!\n");
        queue dummy = {-1, INF, -1};
        return dummy;
    }
    queue root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    min_heapify(pq, 0);
    return root;
}

void decreaseKey(MinPQ *pq, int i, int newKey)
{
    if (i >= pq->size || newKey > pq->heap[i].key)
    {
        printf("Invalid Decrease Operation!\n");
        return;
    }
    pq->heap[i].key = newKey;
    while (i > 0 && pq->heap[(i - 1) / 2].key > pq->heap[i].key)
    {
        swapQueue(&pq->heap[i], &pq->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int findIndex(MinPQ *pq, int vertexIdx)
{
    for (int i = 0; i < pq->size; i++)
    {
        if (pq->heap[i].idx == vertexIdx)
            return i;
    }
    return -1;
}


void primMST(Graph *graph, int start)
{
    int V = graph->numVertex;
    int *key = (int *)malloc(V * sizeof(int)); // Keeps track of key values O(n)
    int *parent = (int *)malloc(V * sizeof(int)); // Keeps track of the parent of those keys O(n)
    for (int i = 0; i < V; i++)
    {
        key[i] = INF;
        parent[i] = -1;
    }
    key[start] = 0;

    MinPQ pq;
    pq.size = 0;
    for (int i = 0; i < V; i++)
    {
        queue element;
        element.idx = i;
        element.key = key[i];
        element.parent = parent[i];
        insertMinPQ(&pq, element);
    }

    while (pq.size > 0)
    {
        queue uElem = extractMin(&pq);
        int u = uElem.idx;

        for (int j = 0; j < graph->g[u].deg; j++)
        {
            int v = graph->g[u].arr[j].adj;
            int wt = graph->g[u].arr[j].wt;
            int pos = findIndex(&pq, v);

            if (pos != -1 && wt<key[v])
            {
                key[v] = key[u] + wt;
                parent[v] = u;
                pq.heap[pos].key = key[v];
                pq.heap[pos].parent = u;
                decreaseKey(&pq, pos, key[v]);
            }
        }
    }

    printf("Minimal Spanning Tree is :\n");
    printf("Edge\t\tWeight\n");
    for (int i = 0; i < V; i++)
    {
        if (parent[i] != -1)
        {
            printf("%d - %d\t\t %d\n", parent[i],i,key[i]);
        }
    }

    free(key);
    free(parent);
}

int main()
{
    int start;
    Graph *graph = readGraph("graph.txt");
    if (!graph)
    {
        printf("Error reading graph file\n");
        return 1;
    }
    printGraph(graph);
    printf("Enter the starting Vertex: ");
    scanf("%d", &start);
    primMST(graph, start);
    freeGraph(graph);
    return 0;
}
