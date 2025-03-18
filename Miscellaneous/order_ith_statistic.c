#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisonCount = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisonCount++;
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int randomized_partition(int arr[], int low, int high)
{
    int randomIndex = low + rand() % (high - low + 1);
    swap(&arr[randomIndex], &arr[high]);
    return partition(arr, low, high);
}

int randomized_select(int arr[], int low, int high, int i)
{
    if (low == high)
    {
        return arr[low];
    }

    int q = randomized_partition(arr, low, high);
    int k = q - low + 1;

    if (i == k)
        return arr[q];
    else if (i < k)
        return randomized_select(arr, low, q - 1, i);
    else
        return randomized_select(arr, q + 1, high, i - k);
}

int main()
{
    int n, i;

    srand(time(0));

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements: ");
    for (int j = 0; j < n; j++)
    {
        scanf("%d", &arr[j]);
    }

    printf("Enter the value of i (1 to %d): ", n);
    scanf("%d", &i);

    if (i < 1 || i > n)
    {
        printf("Invalid input! i must be between 1 and %d.\n", n);
        return 1;
    }

    comparisonCount = 0;

    int result = randomized_select(arr, 0, n - 1, i);

    printf("The %d-th smallest element is: %d\n", i, result);
    printf("Number of comparisons: %d\n", comparisonCount);

    return 0;
}