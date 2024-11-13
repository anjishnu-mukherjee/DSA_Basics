#include <stdio.h>
#include <stdlib.h>


int linear_search(int *a, int size, int key) 
{
    for (int i = 0; i < size; i++) 
    {
        if (a[i] == key) 
        {
            return i;
        }
    }
    return -1;
}


void bubble_sort(int *a, int *index, int size) 
{
    int temp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++) 
        {
            if (a[j] > a[j + 1]) 
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }
}


int binary_search(int *a, int size, int key) 
{
    int *index = (int *)malloc(size * sizeof(int));
    if (index == NULL) 
    {
        printf("Memory allocation failed\n");
        return -1;
    }
    
    for (int i = 0; i < size; i++) 
    {
        index[i] = i;
    }
    
    bubble_sort(a, index, size);

    int low = 0, high = size - 1, mid;
    while (low <= high) 
    {
        mid = low + (high - low) / 2;
        if (a[mid] == key) 
        {
            int result = index[mid];
            free(index);
            return result;
        } else if (a[mid] > key) 
        {
            high = mid - 1;
        } else 
        {
            low = mid + 1;
        }
    }
    
    free(index);
    return -1;
}


int interpolation_search(int *a, int size, int key) 
{
    int *index = (int *)malloc(size * sizeof(int));
    if (index == NULL) 
    {
        printf("Memory allocation failed\n");
        return -1;
    }
    
    for (int i = 0; i < size; i++) 
    {
        index[i] = i;
    }
    
    bubble_sort(a, index, size);

    int low = 0, high = size - 1, pos;
    while (low <= high && key >= a[low] && key <= a[high]) 
    {
        if (a[high] == a[low]) 
        {
            if (a[low] == key) 
            {
                int result = index[low];
                free(index);
                return result;
            }
            break;
        }
        pos = low + ((key - a[low]) * (high - low) / (a[high] - a[low]));
        if (a[pos] == key) 
        {
            int result = index[pos];
            free(index);
            return result;
        } 
        else if (a[pos] < key) 
        {
            low = pos + 1;
        } else 
        {
            high = pos - 1;
        }
    }

    free(index);
    return -1;
}


int main() 
{
    int size, choice, key, res;
    
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    
    int *a = (int *)malloc(size * sizeof(int));
    if (a == NULL) 
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) 
    {
        scanf("%d", &a[i]);
    }
    
    while (1) 
    {
        printf("\nChoose a search technique:\n");
        printf("1. Linear Search\n");
        printf("2. Binary Search\n");
        printf("3. Interpolation Search\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 4) 
        {
            break;  
        }
        
        printf("Enter the element to search for: ");
        scanf("%d", &key);
        
        switch (choice) 
        {
            case 1:
                res = linear_search(a, size, key);
                if (res != -1) 
                {
                    printf("Your key: %d is in position: %d\n", key, res);
                } else 
                {
                    printf("Element not found\n");
                }
                break;
                
            case 2:
                res = binary_search(a, size, key);
                if (res != -1) 
                {
                    printf("Your key: %d is in position: %d\n", key, res);
                } else 
                {
                    printf("Element not found\n");
                }
                break;
                
            case 3:
                res = interpolation_search(a, size, key);
                if (res != -1) 
                {
                    printf("Your key: %d is in position: %d\n", key, res);
                } else 
                {
                    printf("Element not found\n");
                }
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    free(a);
    return 0;
}