/*
Propose an algorithm to remove duplicates from an ordered array, without using any second
array. For example, if the original content of the array is: 1, 1, 3, 4, 8, 8, 10, 10, 25, 28, 30, 30, 30;
then the final content of the array should be 1,3,4,8,10,25,28,30. What is the time complexity of
the proposed algorithm?
*/

#include <stdio.h>

int remove_duplicates(int a[],int n)
{
    if (n ==0)
        return 0;
    
    int i =0;
    for (int j =1;j<n;j++)
    {
        if (a[i] != a[j])
        {
            i ++;
            a[i] = a[j];
        }
    }

    return i+1;
}

int main()
{
    int size ;
    printf("Enter the size of the array\n>");
    scanf("%d",&size);

    int a[size];
    printf("Enter the Elements in ordered fashion in the array!\n");
    for (int i =0; i< size;i++)
    {
        printf("Enter element %d :> ",i);
        scanf("%d",&a[i]);
    }

    size = remove_duplicates(a,size);
    printf("\nNew array: ");

    for(int i =0; i<size;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}

/*
Time Complexity of this algorithm is O(n) as the j traverses through the whole array once
*/