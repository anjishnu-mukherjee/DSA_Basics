#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    int u;
    int v;
    int wt;
} Edge;

typedef struct {
    int parent;
    int rank;
}Subset;

Edge edges[MAX];
Edge mst[MAX];
int edgecount = 0;

int unionfind(Subset subsets[],int i)
{
    if (subsets[i].parent != i)
    {
        subsets[i].parent = unionfind(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unionset(Subset subsets[], int x, int y)
{
    int xr = unionfind(subsets,x);
    int yr = unionfind(subsets,y);

    if (xr == yr)
        return;

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
        subsets[yr].parent = xr;
        subsets[xr].rank ++;
    }
}

void readGraphfromfile(char *filename, int *V, int *E)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file\n");
        exit(1);
    }

    fscanf(file,"%d %d",V,E);
    for (int i = 0; i< *E ; i++)
    {
        fscanf(file,"%d %d %d", &edges[i].u, &edges[i].v,&edges[i].wt);
        edgecount++;
    }

    fclose(file);
}


void swap(Edge *a, Edge *b)
{
    Edge temp = *a;
    *a = *b;
    *b = temp;
}


int partition(Edge arr[], int low , int high)
{
    int pi = arr[high].wt;
    int i = low-1;

    for (int j = low; j<high; j++)
    {
        if (arr[j].wt <pi)
        {
            i++;
            swap(&arr[i],&arr[j]);
        }
    }

    swap(&arr[i+1],&arr[high]);
    return i+1;
}

void quicksort(Edge arr[], int low, int high)
{
    if (low<high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr,low,pi-1);
        quicksort(arr,pi+1,high);
    }
}

void kruskals(int V)
{
    Subset *subsets = (Subset *)malloc(V * sizeof (Subset));

    for (int i =0; i< V; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    quicksort(edges, 0, edgecount-1);

    int mstEdges = 0;
    for (int i = 0; i<edgecount && mstEdges <V-1; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        int set_u = unionfind(subsets,u);
        int set_v = unionfind(subsets,v);

        if (set_u != set_v)
        {
            mst[mstEdges++] = edges[i];
            unionset(subsets, set_u, set_v);
        }
    }

    int totalwt = 0;
    printf("Minimum Spanning Tree Edges:\n");
    for (int i = 0; i<mstEdges; i++)
    {
        printf("%d - %d: [%d]\n",mst[i].u, mst[i].v, mst[i].wt);
        totalwt += mst[i].wt;
    }

    printf("Total weight of MST: %d\n", totalwt);
    free(subsets);
}

int main()
{
    int V,E;
    readGraphfromfile("graph2.txt", &V, &E);
    kruskals(V);
    return 0;
}