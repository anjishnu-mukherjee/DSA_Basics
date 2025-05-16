#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct{
    int u; int v;
}Edge;

typedef struct{
    int parent;
    int rank;
} Subset;

Edge edges[MAX];
Edge graph[MAX];

int edgecount;
int graphcount;

int unionfind(Subset *subsets, int x)
{
    if (subsets[x].parent != x)
    {
        subsets[x].parent = unionfind(subsets, subsets[x].parent);
    }
    return subsets[x].parent;
}

void unionset(Subset *subsets, int x, int y)
{
    int xr = unionfind(subsets,x);
    int yr = unionfind(subsets,y);

    if (subsets[xr].rank < subsets[yr].rank)
    {
        subsets[xr].parent = yr;
    }
    else if (subsets[xr].rank > subsets[yr].rank)
    {
        subsets[yr].parent = xr;
    }
    else
    {
        subsets[xr].parent = yr;
        subsets[yr].rank++;
    }
}

void printComponents(Subset *subsets,int V)
{
    printf("Vertex\tParent\n");
    for (int i = 0; i< V; i++)
    {
        printf("%d\t%d\n",i,subsets[i].parent);
    }
}

int connectedComponents(int V, int E)
{
    Subset * subsets = (Subset *)malloc(V*sizeof(Subset));

    int components = V;

    for (int i =0; i< V; i++)
    {
        subsets[i].parent  = i;
        subsets[i].rank = 0;
    }

    for (int i =0; i< E; i++)
    {
        int set_u = unionfind(subsets,edges[i].u);
        int set_v = unionfind(subsets,edges[i].v);

        if (set_u != set_v)
        {
            graph[graphcount++] = edges[i];
            unionset(subsets, edges[i].u, edges[i].v);
            components --;
        }
    }

    printComponents(subsets,V);

    return components;
}

void readFromGraph(int *V, int *E)
{
    FILE *fp = fopen("graph.txt","r");
    if (!fp)
    {
        printf("Error Opening File!\n");
        return;
    }

    fscanf(fp, "%d %d", V, E);
    for (int i =0; i< *E; i++)
    {
        int u,v;
        fscanf(fp , "%d %d", &u,&v);
        edges[i].u = u;
        edges[i].v = v;
    }
    fclose(fp);
}

int main()
{
    int V, E;
    readFromGraph(&V, &E);

    printf("\nEdges in the graph: ");
    for(int i =0; i< E; i++)
    {
        printf("%d - %d",edges[i].u, edges[i].v);
        printf("\n");
    }
    printf("\n");
    int components = connectedComponents(V, E);
    printf("\nNumber of Connected Components: %d\n",components);

    printf("MST Considered: \n");
    for(int i =0 ; i< graphcount; i++)
    {
        printf("%d - %d",graph[i].u,graph[i].v);
        printf("\n");
    }
    return 0;
}