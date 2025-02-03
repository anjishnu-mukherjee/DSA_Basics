#include <stdio.h>

int tailrecsum(int a , int b)
{
    printf("Call : [%d,%d]\n",a,b);
    if (a==0)
    {
        return b;
    }
    return tailrecsum(a-1,b+a);
}

int main()
{
    int n;
    printf("\nEnter the limit\n>");
    scanf("%d",&n);

    int sum = tailrecsum(n,0);
    printf("Sum : %d",sum);
    return 0;
}