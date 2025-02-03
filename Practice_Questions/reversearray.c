/*
How can you reverse an array without using an extra array? Provide the algorithm and analyze its
time and space complexity.
*/

#include <stdio.h>

int main()
{
    int size ;
    printf("Enter the size of the array\n>");
    scanf("%d",&size);

    int a[size];
    for (int i =0; i< size;i++)
    {
        printf("Enter element %d :> ",i);
        scanf("%d",&a[i]);
    }

    printf("The original Array: ");
    for (int i =0; i< size;i++)
    {
        printf("%d ",a[i]);
    }

    int start = 0;
    int finish = size-1;
    int temp;

    while(start<=finish)
    {
        temp = a[start];
        a[start] = a[finish];
        a[finish] = temp;

        start ++;
        finish --;
    }

    printf("\nThe modified Array: ");
    for (int i =0; i< size;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}

/*
Time Complexity : O(n) -> the while loop runs n/2 times
Space Complexity : O(1) -> no additional storage is used
*/