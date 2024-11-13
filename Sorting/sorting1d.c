#include <stdio.h>
#include <stdlib.h>

int improved_bubble_sort(int *a, int n)
{
    int flag = n-1;
    int temp,c=0;
    while (flag > 0)
    {
        c++;
        int new_flag = 0;
        for (int i = 0; i<flag; i++)
        {
            if (a[i]>a[i+1])
            {
                temp = a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
                new_flag = i;
            }
        }
        flag=new_flag;
    }
    return c;
}


int insertion_sort(int *a,int n)
{
    int key,j ,c=0;
    for (int i = 1;i<n;i++)
    {
        key = a[i];
        j = i-1;
        while(j>=0 && a[j]>key)
        {
            a[j+1]=a[j];
            j--;
            c++;
        }
        a[j+1]=key;
    }
    return c;
}


int counting_sort(int *a,int *b,int n,int k)
{
    int count=0;
    int c[k+1];
    for (int i =0;i<=k;i++)
    {
        c[i]=0;
    }
    for (int i =0;i<n;i++)
    {
        c[a[i]]= c[a[i]]+1;
    }
    for(int i=1;i<=k;i++)
    {
        c[i]=c[i]+c[i-1];
    }
    
    for(int i =0;i<=k;i++)
    {
        printf("%d ",c[i]);
    }
    printf("\n");

    for (int i = n-1;i>=0;i--)
    {
        count++;
        b[c[a[i]]-1]=a[i];
        c[a[i]]=c[a[i]]-1;
    }
    return count;
}


int main()
{
    int size, choice, c;
    printf("Enter size of array: ");
    scanf("%d", &size);

    int* ptr = (int*)malloc(size * sizeof(int));

    printf("Enter the elements of the Array:\n");
    for (int i = 0; i < size; i++)
    {
        printf("Element %d: ", i + 1);
        scanf("%d", &ptr[i]);
    }

    printf("Choose sorting algorithm:\n");
    printf("1. Improved Bubble Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Counting Sort\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            printf("Your Array before improved bubble sort: \n");
            for (int i = 0; i < size; i++)
            {
                printf("%d ", ptr[i]);
            }
            printf("\n");

            c = improved_bubble_sort(ptr, size);

            printf("Your Array after improved bubble sort: \n");
            for (int i = 0; i < size; i++)
            {
                printf("%d ", ptr[i]);
            }
            printf("\nNumber of comparisons: %d\n", c);
            break;

        case 2:
            printf("Your Array before insertion sort: \n");
            for (int i = 0; i < size; i++)
            {
                printf("%d ", ptr[i]);
            }
            printf("\n");

            c = insertion_sort(ptr, size);

            printf("Your Array after insertion sort: \n");
            for (int i = 0; i < size; i++)
            {
                printf("%d ", ptr[i]);
            }
            printf("\nNumber of comparisons: %d\n", c);
            break;

        case 3:
            printf("Your Array before counting sort: \n");
            for (int i = 0; i < size; i++)
            {
                printf("%d ", ptr[i]);
            }
            printf("\n");
            int max=ptr[0];
            for(int i=1;i<size;i++)
            {
                if (ptr[i]>max)
                {
                    max = ptr[i];
                }
            }
            int *rptr = (int *)malloc(size*sizeof(int));
            for (int i =0;i<size;i++)
            {
                rptr[i]=0;
            }
            c = counting_sort(ptr,rptr, size,max);

            printf("Your Array after counting sort: \n");
            for (int i = 0; i < size; i++)
            {
                printf("%d ", rptr[i]);
            }
            printf("\nNumber of comparisons: %d\n", c);
            free(rptr);
            break;

        default:
            printf("Invalid choice.\n");
    }
    free(ptr);
    return 0;
}