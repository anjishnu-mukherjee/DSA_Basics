#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void cocktailShakerSort(int arr[], int n) 
{
    int swapped = 1;
    int start = 0;
    int end = n - 1;

    while (swapped) 
    {
        swapped = 0;

        for (int i = start; i < end; i++) 
        {
            if (arr[i] > arr[i + 1]) 
            {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped)
            break;

        swapped = 0;

        end--;

        for (int i = end - 1; i >= start; i--) 
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }

        start++;
    }
}


void printArray(int arr[], int size) 
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void randomgenerate(int * a, int size)
{
    int num;
    srand(time(0));

    for (int i =0;i<size;i++)
    {
        num = rand()% 101 + 1;
        a[i] = num;
    }
}

int main() 
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d",&size);
    int *arr = (int *)malloc(sizeof(int)*size);

    randomgenerate(arr,size);

    printf("Original array: \n");
    printArray(arr,size);

    cocktailShakerSort(arr, size);

    printf("Sorted array: \n");
    printArray(arr, size);

    return 0;
}
