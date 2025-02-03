#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct node 
{
    int vertex;
    struct node *next;
} node;

typedef struct Graph 
{
    int numVertex;
    node **AdjList;
} Graph;

int time = 0; // Global time counter for DFS

node *createNode(int v) 
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph *create_graph(int vertices) 
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertex = vertices;

    graph->AdjList = (node **)malloc(vertices * sizeof(node *));
    for (int i = 0; i < vertices; i++) 
    {
        graph->AdjList[i] = NULL;
    }

    return graph;
}

void add_edge(Graph *graph, int src, int dest) 
{
    node *newNode = createNode(dest);
    newNode->next = graph->AdjList[src];
    graph->AdjList[src] = newNode;

    // Since it's an undirected graph, add the reverse edge
    newNode = createNode(src);
    newNode->next = graph->AdjList[dest];
    graph->AdjList[dest] = newNode;
}

void print_graph(Graph *graph) 
{
    for (int v = 0; v < graph->numVertex; v++) 
    {
        node *temp = graph->AdjList[v];
        printf("\nAdjacency list of vertex %d:\n", v);
        while (temp) 
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void dfs_visit(Graph *graph, int u, char *color, int *d, int *f, int *pi) 
{
    time++;
    d[u] = time;      // Discovery time
    color[u] = 'g';   // visiting

    printf("Visiting vertex %d at time %d\n", u, d[u]);

    node *temp = graph->AdjList[u];
    while (temp) 
    {
        int v = temp->vertex;
        if (color[v] == 'w') 
        { // unvisited
            pi[v] = u;
            dfs_visit(graph, v, color, d, f, pi);
        }
        temp = temp->next;
    }

    color[u] = 'b'; // fully explored
    time++;
    f[u] = time; // Finish time

    printf("Finished vertex %d at time %d\n", u, f[u]);
}

void dfs(Graph *graph) 
{
    char color[graph->numVertex];
    int d[graph->numVertex], f[graph->numVertex], pi[graph->numVertex];

    for (int i = 0; i < graph->numVertex; i++) 
    {
        color[i] = 'w';  // Mark all nodes as unvisited (white)
        pi[i] = -1;      // No predecessor
        d[i] = f[i] = 0; // Initialize discovery & finish times
    }

    for (int i = 0; i < graph->numVertex; i++) 
    {
        if (color[i] == 'w') 
        { // Start DFS from unvisited node
            dfs_visit(graph, i, color, d, f, pi);
        }
    }

    printf("\nVertex  Discovery Time  Finish Time  Predecessor\n");
    for (int i = 0; i < graph->numVertex; i++) 
    {
        printf("%4d     %4d             %4d           %4d\n", i, d[i], f[i], pi[i]);
    }
}

int main() 
{
    Graph *graph = create_graph(7);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    add_edge(graph, 2, 4);
    add_edge(graph, 3, 5);
    add_edge(graph, 4, 5);
    add_edge(graph, 5, 6);

    print_graph(graph);

    printf("\nDepth-First Search Traversal:\n");
    dfs(graph);

    return 0;
}
