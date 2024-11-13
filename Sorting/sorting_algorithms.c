#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int heap_size;

int improved_bubble_sort(int *a, int n)
{
    int flag = n-1;
    int temp, c = 0;
    while (flag > 0)
    {
        int new_flag = 0;
        for (int i = 0; i < flag; i++)
        {
            c++;
            if (a[i] > a[i+1])
            {
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                new_flag = i;
            }
        }
        flag = new_flag;
    }
    return c;
}

int insertion_sort(int *a, int n)
{
    int key, j, c = 0;
    for (int i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;
        c++;
        while (j >= 0 && a[j] > key)
        {
            a[j+1] = a[j];
            j--;
            c++;
        }
        a[j+1] = key;
    }
    return c;
}

int counting_sort(int *a, int *b, int n, int k)
{
    int count = 0;
    int c[k+1];
    for (int i = 0; i <= k; i++)
    {
        c[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        c[a[i]] = c[a[i]] + 1;
    }
    for (int i = 1; i <= k; i++)
    {
        c[i] = c[i] + c[i-1];
    }

    for (int i = n-1; i >= 0; i--)
    {
        count++;
        b[c[a[i]]-1] = a[i];
        c[a[i]] = c[a[i]] - 1;
    }
    return count;
}

int selection_sort(int *arr, int n)
{
    int c = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            c++;
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
    return c;
}

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

void max_heapify(int *A, int i, int *count)
{
    int l = left(i);
    int r = right(i);
    int largest;
  
    if (l < heap_size && A[l] > A[i])
    {
        largest = l;
    }
    else
    {
        largest = i;
    }

    if (r < heap_size && A[r] > A[largest])
    {
        largest = r;
    }

    (*count)++;
    if (largest != i)
    {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        max_heapify(A, largest, count);
    }
}

void build_max_heap(int *A, int n, int *count)
{
    heap_size = n;
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        max_heapify(A, i, count);
    }
}

int heap_sort(int *A, int n)
{
    int count = 0;  // Initialize the comparison counter
    build_max_heap(A, n, &count);

    for (int i = n - 1; i > 0; i--)
    {
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;

        heap_size--;
        max_heapify(A, 0, &count);
    }
    return count;
}

void write_output_to_file(const char *filename, int arr[], int n, int comparisons, const char *sort_name)
{
    FILE *file = fopen(filename, "a");
    if (!file)
    {
        printf("Unable to open file.\n");
        exit(1);
    }
    fprintf(file, "%s\n", sort_name);
    fprintf(file, "Sorted Array: \n");
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }
    fprintf(file, "\nTotal Number of Comparisons: %d\n", comparisons);
    fclose(file);
}

void read_array_from_file(const char *filename, int **arr, int size)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Unable to open file.\n");
        exit(1);
    }
    *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        fscanf(file, "%d", &(*arr)[i]);
    }
    fclose(file);
}

void generate_random_numbers(int size)
{
    FILE *fptr;
    int num;

    srand(time(0));

    fptr = fopen("input.txt", "w");
    if (fptr == NULL)
    {
        printf("Error opening the file!\n");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        num = rand() % 101 + 1;
        fprintf(fptr, "%d ", num);
    }

    fclose(fptr);

    printf("Successfully written %d random numbers to 'input.txt'.\n", size);
}

int main()
{
    int *arr, n;
    int comparisons;

    n = 10;  // Example size
    generate_random_numbers(n);

    // Read array from input file
    read_array_from_file("input.txt", &arr, n);

    // Prepare the output file by clearing its contents initially
    FILE *file = fopen("output.txt", "w");
    fclose(file);  // Just opening and closing to clear the content if it exists

    // Perform Improved Bubble Sort
    int *arr_copy = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr_copy[i] = arr[i];
    comparisons = improved_bubble_sort(arr_copy, n);
    write_output_to_file("output.txt", arr_copy, n, comparisons, "Improved Bubble Sort");

    // Perform Insertion Sort
    for (int i = 0; i < n; i++) arr_copy[i] = arr[i];
    comparisons = insertion_sort(arr_copy, n);
    write_output_to_file("output.txt", arr_copy, n, comparisons, "Insertion Sort");

    // Perform Selection Sort
    for (int i = 0; i < n; i++) arr_copy[i] = arr[i];
    comparisons = selection_sort(arr_copy, n);
    write_output_to_file("output.txt", arr_copy, n, comparisons, "Selection Sort");

    // Perform Count Sort (counting sort example with range 0-100)
    int *b = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr_copy[i] = arr[i];
    comparisons = counting_sort(arr_copy, b, n, 100);
    write_output_to_file("output.txt", b, n, comparisons, "Counting Sort");

    // Perform Heap Sort
    for (int i = 0; i < n; i++) arr_copy[i] = arr[i];
    comparisons = heap_sort(arr_copy, n);
    write_output_to_file("output.txt", arr_copy, n, comparisons, "Heap Sort");

    // Free allocated memory
    free(arr);
    free(arr_copy);
    free(b);

    return 0;
}
