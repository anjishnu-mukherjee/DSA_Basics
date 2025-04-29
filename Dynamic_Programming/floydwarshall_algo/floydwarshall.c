#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

void printSolution(int dist[MAX_VERTICES][MAX_VERTICES], int n, int parent[MAX_VERTICES][MAX_VERTICES]);
void printPath(int parent[MAX_VERTICES][MAX_VERTICES], int i, int j);

void floydWarshall(int graph[MAX_VERTICES][MAX_VERTICES], int n)
{
    int dist[MAX_VERTICES][MAX_VERTICES];  
    int parent[MAX_VERTICES][MAX_VERTICES]; 

    // Initialize parent and distance
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = graph[i][j];

            if (i == j)
            {
                parent[i][j] = -1; // No parent for diagonal
            }
            else if (graph[i][j] != INF)
            {
                parent[i][j] = i; // Direct edge exists
            }
            else
            {
                parent[i][j] = -1; // No path initially
            }
        }
    }

    
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }

    
    printSolution(dist, n, parent);
}

void printSolution(int dist[MAX_VERTICES][MAX_VERTICES], int n, int parent[MAX_VERTICES][MAX_VERTICES])
{
    printf("Distance Matrix (D):\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
            {
                printf("%7s", "INF");
            }
            else
            {
                printf("%7d", dist[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nParent Matrix (P):\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%7d", parent[i][j]);
        }
        printf("\n");
    }

    
    printf("\nSample Paths:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && parent[i][j] != -1)
            {
                printf("Shortest path from %d to %d: ", i, j);
                printPath(parent, i, j);
                printf(" (Cost: %d)\n", dist[i][j]);
            }
        }
    }
}

void printPath(int parent[MAX_VERTICES][MAX_VERTICES], int i, int j)
{
    if (i == j)
    {
        printf("%d", i);
    }
    else if (parent[i][j] == -1)
    {
        printf("No path exists");
    }
    else
    {
        printPath(parent, i, parent[i][j]);
        printf(" -> %d", j);
    }
}

void readfromfile(int graph[MAX_VERTICES][MAX_VERTICES], int *n)
{
    FILE *file = fopen("floydwarshallgraph.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fscanf(file, "%d", n);

    for (int i = 0; i < *n; i++)
    {
        for (int j = 0; j < *n; j++)
        {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    int vertex, degree, neighbor, weight;
    while (fscanf(file, "%d %d", &vertex, &degree) == 2)
    {
        for (int i = 0; i < degree; i++)
        {
            fscanf(file, "%d %d", &neighbor, &weight);
            graph[vertex][neighbor] = weight;
        }
    }

    fclose(file);
}

int main()
{
    int n; 
    int graph[MAX_VERTICES][MAX_VERTICES];
    
    readfromfile(graph, &n);

    floydWarshall(graph, n);

    return 0;
}