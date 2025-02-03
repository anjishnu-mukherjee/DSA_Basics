#include <stdio.h>

int fibo(int n, int a, int b)
{
    if (n == 0)
    {
        return a;
    }
    else if (n == 1)
    {
        return b;
    }
    return fibo(n-1,b,a+b); // tail recursion
}

int main()
{
    int n;
    printf("\nEnter the number of elements for printing Fibonacci\n>");
    scanf("%d",&n);
    for (int i =0;i<n;i++)
    {
        printf("%d ",fibo(i,0,1));
    }
    return 0;
}