#include <stdio.h>
#include <stdlib.h>

typedef struct vertex
{
    int key;
    int parent;
    int idx;
} Node;

typedef struct adjArr
{
    int degree;
    Node *vertex;
} AdjArr;

typedef struct graph
{
    int numVertices;
    Node *vertices;
    AdjArr *adjList;
    int **weights;
} Graph;

void minHeapify(Node *arr, int i, int size, int *pos)
{
    int l = 2 * i + 1, r = 2 * i + 2, min = i;
    if (l < size && arr[l].key < arr[min].key)
        min = l;
    if (r < size && arr[r].key < arr[min].key)
        min = r;
    if (min != i)
    {
        pos[arr[i].idx] = min;
        pos[arr[min].idx] = i;
        Node t = arr[i];
        arr[i] = arr[min];
        arr[min] = t;
        minHeapify(arr, min, size, pos);
    }
}

void buildMinHeap(Node *arr, int size, int *pos)
{
    for (int i = (size / 2) - 1; i >= 0; i--)
        minHeapify(arr, i, size, pos);
}

Node dequeue(Node *arr, int *size, int *pos)
{
    if (*size <= 0)
    {
        printf("Heap Underflow\n");
        return (Node){9999, -1, -1};
    }
    Node min = arr[0];
    arr[0] = arr[--(*size)];
    pos[arr[0].idx] = 0;
    minHeapify(arr, 0, *size, pos);
    return min;
}

void heapDecreaseKey(Node *arr, int i, int newKey, int size, int *pos)
{
    arr[i].key = newKey;
    while (i > 0 && arr[(i - 1) / 2].key > arr[i].key)
    {
        pos[arr[i].idx] = (i - 1) / 2;
        pos[arr[(i - 1) / 2].idx] = i;
        Node temp = arr[i];
        arr[i] = arr[(i - 1) / 2];
        arr[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Graph *createGraph(int numVertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjList = (AdjArr *)malloc(numVertices * sizeof(AdjArr));
    graph->vertices = (Node *)malloc(numVertices * sizeof(Node));
    graph->weights = (int **)malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; i++)
    {
        graph->weights[i] = (int *)calloc(numVertices, sizeof(int));
        graph->vertices[i] = (Node){9999, -1, i};
        graph->adjList[i].degree = 0;
        graph->adjList[i].vertex = (Node *)malloc(numVertices * sizeof(Node));
    }
    return graph;
}

void readGraphFromFile(Graph *graph)
{
    FILE *file = fopen("graph.txt", "r");
    if (!file)
    {
        printf("Error opening input file!\n");
        exit(1);
    }
    int numVertices;
    fscanf(file, "%d", &numVertices);
    for (int i = 0; i < numVertices; i++)
    {
        int vertex, degree, neighbor, weight;
        fscanf(file, "%d %d", &vertex, &degree);
        graph->adjList[vertex].degree = degree;
        for (int j = 0; j < degree; j++)
        {
            fscanf(file, "%d %d", &neighbor, &weight);
            graph->weights[vertex][neighbor] = weight;
        }
    }
    fclose(file);
}

void printGraph(Graph *graph)
{
    printf("Initial Graph:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (graph->weights[i][j] != 0)
                printf("(%d, %d) ", j, graph->weights[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void prims(Graph *graph, int s)
{
    int n = graph->numVertices, heapSize = n;
    Node *queue = (Node *)malloc(n * sizeof(Node));
    int *pos = (int *)malloc(n * sizeof(int));
    int *inMST = (int *)calloc(n, sizeof(int));
    int totalWeight = 0;
    
    for (int i = 0; i < n; i++)
    {
        queue[i] = graph->vertices[i];
        pos[i] = i;
    }
    queue[s].key = 0;
    buildMinHeap(queue, n, pos);
    
    while (heapSize > 0)
    {
        Node u = dequeue(queue, &heapSize, pos);
        inMST[u.idx] = 1;
        totalWeight += u.key;
        
        for (int v = 0; v < n; v++)
        {
            if (graph->weights[u.idx][v] && !inMST[v] && graph->weights[u.idx][v] < graph->vertices[v].key)
            {
                graph->vertices[v].parent = u.idx;
                graph->vertices[v].key = graph->weights[u.idx][v];
                heapDecreaseKey(queue, pos[v], graph->weights[u.idx][v], heapSize, pos);
            }
        }
    }
    free(queue);
    free(pos);
    free(inMST);
    printf("Total weight of MST: %d\n", totalWeight);
}

void printMST(Graph *graph)
{
    printf("Vertex\t   Predecessor\tKey\n");
    for (int v = 0; v < graph->numVertices; v++)
        printf("%d\t\t%d\t\t%d\n", graph->vertices[v].idx, graph->vertices[v].parent, graph->vertices[v].key);
    printf("\n");
}

int main()
{
    FILE *file = fopen("graph.txt", "r");
    if (!file)
    {
        printf("Error opening input file!\n");
        return 1;
    }
    int n, s;
    fscanf(file, "%d", &n);
    fclose(file);
    Graph *graph = createGraph(n);
    readGraphFromFile(graph);
    printGraph(graph);
    printf("Enter source index\n");
    scanf("%d", &s);
    prims(graph, s);
    printf("After Prim's -> MST\n");
    printMST(graph);
    return 0;
}
