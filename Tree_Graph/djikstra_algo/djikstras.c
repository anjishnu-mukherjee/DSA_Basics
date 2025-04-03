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
    fscanf(fp, "%d", &(graph->numVertex));
    int V = graph->numVertex;
    graph->g = (vertex *)malloc(V * sizeof(vertex));

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
    printf("Graph Representation:\n");
    for (int i = 0; i < graph->numVertex; i++)
    {
        printf("%d -> ", i);
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
    for (int i = 0; i < graph->numVertex; i++)
    {
        free(graph->g[i].arr);
    }
    free(graph->g);
    free(graph);
}

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
    int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
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
    int i = pq->size++;
    pq->heap[i] = element;
    while (i > 0 && pq->heap[(i - 1) / 2].key > pq->heap[i].key)
    {
        swapQueue(&pq->heap[i], &pq->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

queue extractMin(MinPQ *pq)
{
    queue root = pq->heap[0];
    pq->heap[0] = pq->heap[--pq->size];
    min_heapify(pq, 0);
    return root;
}

void decreaseKey(MinPQ *pq, int i, int newKey)
{
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

void printPath(int *parent, int v)
{
    if (parent[v] == -1 )
    {
        printf("%d", v);
        return;
    }
    printPath(parent, parent[v]);
    printf(" -> %d", v);
}

void dijkstra(Graph *graph, int source, int dest)
{
    int V = graph->numVertex;
    int *dist = (int *)malloc(V * sizeof(int)); // calculates distance O(n)
    int *parent = (int *)malloc(V * sizeof(int)); // keeps track of which the predecessor O(n)
    int *maxEdge = (int *)malloc(V * sizeof(int)); // keeps count of the total weight of the edge O(n)

    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
        maxEdge[i] = 0;
    }
    dist[source] = 0;

    MinPQ pq = {.size = 0};
    for (int i = 0; i < V; i++)
    {
        queue element = {parent[i], dist[i], i};
        insertMinPQ(&pq, element);
    }

    while (pq.size > 0)
    {
        queue uElem = extractMin(&pq);
        int u = uElem.idx;

        for (int j = 0; j < graph->g[u].deg; j++)
        {
            int v = graph->g[u].arr[j].adj;
            int weight = graph->g[u].arr[j].wt;
            int pos = findIndex(&pq, v);

            if (pos != -1 && dist[u] != INF && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                maxEdge[v] = (maxEdge[u] > weight) ? maxEdge[u] : weight;
                pq.heap[pos].key = dist[v];
                pq.heap[pos].parent = u;
                decreaseKey(&pq, pos, dist[v]);
            }
        }
    }

    printf("Vertex\tPredecessor\tDistance\tMax Edge\n");
    for (int i = 0; i < V; i++)
    {
        printf("%d\t%d\t\t", i, parent[i]);
        if (dist[i] == INF)
            printf("INF\t\tINF\n");
        else
            printf("%d\t\t%d\n", dist[i], maxEdge[i]);
        
    }

    for (int i = 0; i< V; i++) // Prints the path from src to des (recursive function)
    {
        printPath(parent,i);
        printf("\n");
    }

    printf("Path from Source to Destination: ");
    printPath(parent,dest);
    free(dist);
    free(parent);
    free(maxEdge);
}

int main()
{
    int source,destination;
    Graph *graph = readGraph("graph.txt");
    if (!graph)
        return 1;
    
    printGraph(graph);
    printf("Enter the source vertex: ");
    scanf("%d", &source);
    printf("Enter the destintion vertex: ");
    scanf("%d",&destination);
    dijkstra(graph, source,destination);
    freeGraph(graph);
    return 0;
}