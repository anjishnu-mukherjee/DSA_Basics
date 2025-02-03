#include <stdio.h>
#include <stdlib.h>

static int front = -1;
static int rear = -1;
static int count = 0;
int queue [100];

void enqueue( int n)
{
    queue[++rear] = n;
    if (rear == 0)
    {
        front = 0;
    }
    count ++;
}

void dequeue()
{
    int temp = queue[front++];
    count --;
    printf("\nVertex Dequeued %d",temp);
}

typedef struct node
{
    int vertex;
    struct node* next;
}node;

typedef struct Graph
{
    int numVertex;
    node ** AdjList;
}Graph;

node* createNode(int v)
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* create_graph(int vertices)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertex = vertices;
    
    graph->AdjList = (node**)malloc(vertices*sizeof(node*));

    for(int i = 0; i<vertices;i++)
    {
        graph->AdjList[i] = NULL;
    }

    return graph;
}

void add_edge(Graph* graph,int src,int dest)
{
    // Adding edge from src to dest
    node* newNode = createNode(dest);
    newNode->next = graph->AdjList[src];
    graph->AdjList[src] = newNode;

    // Adding edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->AdjList[dest];
    graph->AdjList[dest] = newNode;
}

void print_graph(Graph * graph)
{
    for (int v = 0; v<graph->numVertex;v++)
    {
        node* temp = graph->AdjList[v];
        printf("\nAdjacency list of the vertex %d\n",v);
        while(temp)
        {
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("NULL");
        printf("\n");
    }
}

void bfs(Graph * graph, int s, char* color, int* d, int* pi)
{
    int v;
    for (v =0;v<graph->numVertex;v++)
    {
        if (v!=s)
        {
            color[v] = 'w';
            d[v] = 9999;
            pi[v] = -1;
        }
    }
    color[s] = 'g';
    d[s] = 0;
    pi[s] = -1;
    enqueue(s);

    while(count!=0)
    {
        v = queue[front];
        printf("\nVertex %d",v);
        node* temp = graph->AdjList[v];
        while(temp)
        {
            if(color[temp->vertex] == 'w')
            {
                printf("\nInside if of while %d",temp->vertex);
                color[temp->vertex] = 'g';
                d[temp->vertex] = d[v]+1;
                pi[temp->vertex]=v;
                enqueue(temp->vertex);
            }
            temp = temp->next;
        }
        dequeue();
        color[v] = 'b';
    }
}

void print_path(Graph * graph, int s, int v, int* pi)
{
    if (v == s)
    {
        printf("%d ",s);
    }
    else if (pi[v] == -1)
    {
        printf("No path from %d to %d exists",s,v);
    }
    else
    {
        print_path(graph,s,pi[v],pi);
        printf("-> %d ",v);
    }
}

int main()
{
    Graph* graph = create_graph(7);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 4);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 4);
    add_edge(graph, 3, 4);
    add_edge(graph, 4, 6);
    add_edge(graph, 5, 1);
    add_edge(graph, 5, 6);
    print_graph(graph);
    char color[graph->numVertex];
    int d[graph->numVertex],pi[graph->numVertex];

    int v;
    int s=0;

    bfs(graph, s, color, d, pi);
    printf("\nVertex  Color  Distance  Predecessor\n");
    for(v=0; v<graph->numVertex;v++)
        printf("\n  %d       %c      %d         %d\n",v,color[v],d[v],pi[v]);
    printf("\nPredecessor Subgraph\n");

    for(v=0; v<graph->numVertex;v++)
        {
            if(v!=s)
            {   print_path(graph, s, v, pi);
                printf("\n");
            }
        }
    return 0;
}