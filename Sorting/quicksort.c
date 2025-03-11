#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparisonCount = 0;

void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int a[], int low, int high, int pref) 
{
    int pivot;
    
    if (pref == 1) {
        pivot = a[high];
    } 
    else if (pref == 2) {
        swap(&a[low], &a[high]);
        pivot = a[high];
    } 
    else if (pref == 3) {
        int mid = (low + high) / 2;
        swap(&a[mid], &a[high]);
        pivot = a[high];
    } 
    else if (pref == 4) {
        int randIndex = low + rand() % (high - low + 1);
        swap(&a[randIndex], &a[high]);
        pivot = a[high];
    }

    int i = (low - 1);  
    for (int j = low; j < high; j++) 
    {
        comparisonCount++;  
        if (a[j] < pivot) 
        {  
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);  
    return (i + 1);
}

void quicksort(int a[], int low, int high, int pref) 
{
    if (low < high) {
        int pi = partition(a, low, high, pref);
        quicksort(a, low, pi - 1, pref);
        quicksort(a, pi + 1, high, pref);
    }
}

void printArray(int arr[], int size) 
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() 
{
    int ascending[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int descending[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int random[] = {10, 7, 8, 9, 1, 5, 3, 2, 6, 4};
    int size = sizeof(ascending) / sizeof(ascending[0]);
    int arrCopy[size];

    for (int caseNum = 1; caseNum <= 3; caseNum++) 
    {
        int *arr;
        const char *caseName;

        if (caseNum == 1) {
            arr = ascending;
            caseName = "Ascending Order";
        } else if (caseNum == 2) {
            arr = descending;
            caseName = "Descending Order";
        } else {
            arr = random;
            caseName = "Random Order";
        }

        printf("\n*** %s ***\n", caseName);

        for (int pref = 1; pref <= 4; pref++) 
        {
            memcpy(arrCopy, arr, sizeof(arrCopy));
            comparisonCount = 0;

            printf("\nPivot Strategy %d:\n", pref);
            printf("Original array: ");
            printArray(arrCopy, size);

            quicksort(arrCopy, 0, size - 1, pref);

            printf("Sorted array  : ");
            printArray(arrCopy, size);
            printf("Total comparisons: %d\n", comparisonCount);
        }
    }
    return 0;
}
