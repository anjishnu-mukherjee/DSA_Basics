#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparisonCount = 0;

void merge(int a[],int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = lb;
    int b[ub + 1];
    while (i <= mid && j <= ub)
    {
        comparisonCount++;
        if (a[i] <= a[j])
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }
        k++;
    }
    if (i > mid)
    {
        while (j <= ub)
        {
            comparisonCount++;
            b[k] = a[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i <= mid)
        {
            comparisonCount++;
            b[k] = a[i];
            i++;
            k++;
        }
    }
    for (int i = lb; i <= ub; i++)
    {
        a[i] = b[i];
    }
}

void mergeSort(int a[],int lb,int ub)
{
    if (lb<ub)
    {
        int mid = (lb+ub)/2;
        mergeSort(a,lb,mid);
        mergeSort(a,mid+1,ub);
        merge(a,lb,mid,ub);
    }
}

void generatetofile(int n)
{
    FILE *fptr;
    fptr = fopen("input.txt","w");
    for (int i = 1; i <= n; i++)
    {
        fprintf(fptr,"%d ",i);
    }
    fprintf(fptr,"\n");
    for (int i = n; i >= 1; i--)
    {
        fprintf(fptr,"%d ",i);
    }
    fprintf(fptr,"\n");
    for (int i = 1; i <= n; i++)
    {
        fprintf(fptr,"%d ",rand()%(n+1));
    }
    fclose(fptr);
}

void readfromfile(int ascending[],int descending[],int random[],int n)
{
    FILE *fptr;
    fptr = fopen("input.txt","r");
    for (int i = 0; i < n; i++)
    {
        fscanf(fptr,"%d ",&ascending[i]);
    }
    for (int i = 0; i < n; i++)
    {
        fscanf(fptr,"%d ",&descending[i]);
    }
    for (int i = 0; i < n; i++)
    {
        fscanf(fptr,"%d ",&random[i]);
    }
    fclose(fptr);
}


int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    generatetofile(n);
    int ascending[n], descending[n], random[n];
    readfromfile(ascending, descending, random, n);

    FILE *fptr = fopen("output.txt", "w");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fptr, "Ascending order: ");
    for (int i = 0; i < n; i++)
    {
        fprintf(fptr, "%d ", ascending[i]);
    }
    fprintf(fptr, "\n");
    
    comparisonCount = 0;
    mergeSort(ascending, 0, n - 1);
    
    fprintf(fptr, "Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        fprintf(fptr, "%d ", ascending[i]);
    }
    fprintf(fptr, "\n");
    fprintf(fptr, "Number of comparisons: %d\n\n", comparisonCount);

    fprintf(fptr, "Descending order: ");
    for (int i = 0; i < n; i++)
    {
        fprintf(fptr, "%d ", descending[i]);
    }
    fprintf(fptr, "\n");
    
    comparisonCount = 0;
    mergeSort(descending, 0, n - 1);
    
    fprintf(fptr, "Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        fprintf(fptr, "%d ", descending[i]);
    }
    fprintf(fptr, "\n");
    fprintf(fptr, "Number of comparisons: %d\n\n", comparisonCount);

    fprintf(fptr, "Random order: ");
    for (int i = 0; i < n; i++)
    {
        fprintf(fptr, "%d ", random[i]);
    }
    fprintf(fptr, "\n");
    
    comparisonCount = 0;
    mergeSort(random, 0, n - 1);
    
    fprintf(fptr, "Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        fprintf(fptr, "%d ", random[i]);
    }
    fprintf(fptr, "\n");
    fprintf(fptr, "Number of comparisons: %d\n", comparisonCount);
    
    fclose(fptr);
    printf("Output written to output.txt\n");
    return 0;
}
