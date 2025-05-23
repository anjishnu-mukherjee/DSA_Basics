#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int w;
    int p;
}Elements;

Elements * readFromFile(int *n, int *W)
{
    FILE *fp = fopen("KnapSackInput.txt","r");

    if (!fp)
    {
        printf("Error Opening File!");
        exit(0);
    }

    fscanf(fp,"%d %d",n,W);

    Elements * arr = (Elements *)malloc(*n*sizeof(Elements));

    for (int i =0; i<*n; i++)
    {
        fscanf(fp,"%d %d",&arr[i].w,&arr[i].p);
    }

    fclose(fp);
    return arr;
}

void printItems(int ** keep, Elements *arr, int n, int W)
{
    int i = n;
    int w = W;
    printf("Items in the knapsack are:\n");

    while (i > 0 && w > 0)
    {
        if (keep[i][w])
        {
            printf("Item %d (Weight: %d, Profit: %d)\n", i, arr[i-1].w, arr[i-1].p);
            w -= arr[i-1].w;
        }
        i--;
    }
}
int knapSack(Elements *arr, int n, int W)
{
    int **B = (int **)malloc((n + 1) * sizeof(int *));
    int **keep = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
    {
        B[i] = (int *)malloc((W + 1) * sizeof(int));
        keep[i] = (int *)malloc((W + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            B[i][j] = 0;
            keep[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            if (arr[i - 1].w <= j)
            {
                int included = arr[i - 1].p + B[i - 1][j - arr[i - 1].w];
                int excluded = B[i - 1][j];
                if (included > excluded)
                {
                    B[i][j] = included;
                    keep[i][j] = 1;
                }
                else
                {
                    B[i][j] = excluded;
                    keep[i][j] = 0;
                }
            }
            else
            {
                B[i][j] = B[i - 1][j];
                keep[i][j] = 0;
            }
        }
    }

    printItems(keep, arr, n, W);
    int maxProfit = B[n][W];
    for (int i = 0; i <= n; i++)
    {
        free(B[i]);
        free(keep[i]);
    }
    free(B);
    free(keep);
    return maxProfit;
}

int main()
{
    int n, W;

    Elements * arr = readFromFile(&n,&W);
    printf("Weight\tBenifit\n");
    for (int i = 0; i< n; i++)
    {
        printf("%d\t%d\n",arr[i].w,arr[i].p);
    }
    printf("Max Profit is: %d\n",knapSack(arr,n,W));
    free(arr);
    return 0;
}