#include <stdio.h>
#include <stdlib.h>

int heap_size;

int left(int i) 
{
    return 2 * i + 1;
}

int right(int i) 
{
    return 2 * i + 2;
}

int parent(int i) 
{
    return (i - 1) / 2;
}


void max_heapify(int *A, int i) 
{
    int l = left(i);   
    int r = right(i);     
    int largest;

    if (l < heap_size && A[l] > A[i]) 
    {
        largest = l;
    } else 
    {
        largest = i;
    }


    if (r < heap_size && A[r] > A[largest]) 
    {
        largest = r;
    }

    if (largest != i) 
    {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        max_heapify(A, largest); 
    }
}


void build_max_heap(int *A, int n) 
{
    heap_size = n;
    for (int i = n / 2 - 1; i >= 0; i--) 
    {
        max_heapify(A, i);
    }
}

// Function to perform heap sort
void heap_sort(int *A, int n) 
{
    build_max_heap(A, n);

    // One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) 
    {
        // Move current root to the end
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;

        heap_size--; // Reduce heap size
        max_heapify(A, 0); // Max-heapify the reduced heap
    }
}


void print_array(int *A, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int n ;
    printf("Enter the size of the Array: ");
    scanf("%d",&n);
    int *A = (int *)malloc(n*sizeof(int));

    printf("Enter the elements of the array:\n");
    for (int i=0;i<n;i++)
    {
        printf("Element %d: ",i+1);
        scanf("%d",&A[i]);
    }

    printf("Original array: \n");
    print_array(A, n);

    heap_sort(A, n);

    printf("Sorted array: \n");
    print_array(A, n);

    return 0;
}
