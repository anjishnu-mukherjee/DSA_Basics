#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    int destination;
    int weight;
} Edge;

typedef struct adjacencyList
{
    int degree;
    Edge *edges;
} AdjList;

typedef struct minPriorityQueue
{
    int key;
    int parent;
    int index;
} Minpq;

typedef struct graph
{
    int totalVertices;
    Minpq *nodes;
    AdjList *adjList;
} Graph;

void minHeapify(Minpq *arr, int i, int size)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest;
    Minpq temp;

    if (left < size && arr[left].key < arr[i].key)
        smallest = left;
    else
        smallest = i;

    if (right < size && arr[right].key < arr[smallest].key)
        smallest = right;

    if (smallest != i)
    {
        temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        minHeapify(arr, smallest, size);
    }
}

void enqueue(Minpq *arr, int size, int *i, Minpq element)
{
    (*i)++;
    if ((*i) >= size)
    {
        printf("Overflow\n");
        (*i)--;
        return;
    }

    arr[*i] = element;
    int child = *i;
    int parent = (child - 1) / 2;
    Minpq temp;

    while (child > 0 && arr[parent].key > arr[child].key)
    {
        temp = arr[parent];
        arr[parent] = arr[child];
        arr[child] = temp;

        child = parent;
        parent = (child - 1) / 2;
    }
}

Minpq dequeue(Minpq *arr, int size, int *i)
{
    if ((*i) < 0)
    {
        printf("Underflow\n");
        Minpq emptyNode = {9999, -1, -1};
        return emptyNode;
    }
    Minpq min = arr[0];
    arr[0] = arr[(*i)];
    (*i)--;
    minHeapify(arr, 0, (*i) + 1);

    printf("Dequeued %d with key = %d\n", min.index, min.key);
    return min;
}

void heapDecreaseKey(Minpq *arr, int i, int newKey, int heapSize)
{
    if (i < 0 || i > heapSize - 1)
    {
        printf("Invalid Index\n");
        return;
    }

    if (newKey > arr[i].key)
    {
        printf("New key is larger than the current key! Invalid operation.\n");
        return;
    }

    arr[i].key = newKey;

    int child = i;
    int parent = (child - 1) / 2;
    Minpq temp;
    while (child > 0 && arr[parent].key > arr[child].key)
    {
        temp = arr[parent];
        arr[parent] = arr[child];
        arr[child] = temp;

        child = parent;
        parent = (child - 1) / 2;
    }
}

Graph *createGraph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
    {
        printf("Memory allocation failed for graph\n");
        exit(1);
    }

    graph->totalVertices = numVertices;
    graph->adjList = (AdjList *)malloc(numVertices * sizeof(AdjList));
    graph->nodes = (Minpq *)malloc(numVertices * sizeof(Minpq));

    if (!graph->adjList || !graph->nodes)
    {
        printf("Memory allocation failed for graph components\n");
        exit(1);
    }

    for (int i = 0; i < numVertices; i++)
    {
        graph->adjList[i].edges = (Edge *)malloc(numVertices * sizeof(Edge));
    }

    for (int i = 0; i < numVertices; i++)
    {
        graph->nodes[i].key = 9999;
        graph->nodes[i].parent = -1;
        graph->nodes[i].index = i;
        graph->adjList[i].degree = 0;
    }

    return graph;
}

void relax(Graph *graph, int u, int v, Minpq *queue)
{
    int weight = 0;
    for (int i = 0; i < graph->adjList[u].degree; i++)
    {
        if (graph->adjList[u].edges[i].destination == v)
        {
            weight = graph->adjList[u].edges[i].weight;
            break;
        }
    }

    if (graph->nodes[v].key > graph->nodes[u].key + weight)
    {
        graph->nodes[v].key = graph->nodes[u].key + weight;
        graph->nodes[v].parent = u;
        heapDecreaseKey(queue, v, graph->nodes[u].key + weight, graph->totalVertices);
    }
}

void printGraph(Graph *graph)
{
    printf("Graph Representation:\n");
    for (int i = 0; i < graph->totalVertices; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < graph->adjList[i].degree; j++)
        {
            printf("%d[%d] ", graph->adjList[i].edges[j].destination, graph->adjList[i].edges[j].weight);
        }
        printf("\n");
    }
    printf("\n");
}

void dijkstra(Graph *graph, Minpq *queue, int *idx, int source)
{
    graph->nodes[source].key = 0;
    heapDecreaseKey(queue, source, 0, graph->totalVertices);

    for (int i = 0; i < graph->totalVertices; i++)
    {
        enqueue(queue, graph->totalVertices, idx, graph->nodes[i]);
    }

    while ((*idx) != -1)
    {
        Minpq u = dequeue(queue, graph->totalVertices, idx);
        for (int j = 0; j < graph->adjList[u.index].degree; j++)
        {
            int v = graph->adjList[u.index].edges[j].destination;
            relax(graph, u.index, v, queue);
        }
    }
}

Graph *readGraphFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file\n");
        return NULL;
    }
    
    int numVertices;
    fscanf(file, "%d", &numVertices);
    Graph *graph = createGraph(numVertices);
    
    int node, degree, dest, weight;
    while (fscanf(file, "%d %d", &node, &degree) != EOF)
    {
        graph->adjList[node].degree = degree;
        for (int i = 0; i < degree; i++)
        {
            fscanf(file, "%d %d", &dest, &weight);
            graph->adjList[node].edges[i].destination = dest;
            graph->adjList[node].edges[i].weight = weight;
        }
    }
    fclose(file);
    return graph;
}

int main()
{
    Graph *graph = readGraphFromFile("graph.txt");
    if (!graph) return 1;
    printGraph(graph);
    
    Minpq *queue = (Minpq *)malloc(graph->totalVertices * sizeof(Minpq));
    int idx = -1;
    
    int source = 0;
    dijkstra(graph, queue, &idx, source);
    return 0;
}
