#include <stdio.h>

void move(int n, char source, char destination, char spare,int disc);
int main()
{
    int n;
    printf("\nEnter the number of Rings\n>");
    scanf("%d",&n);
    move(n,'A','B','C',n);
    return 0;
}

void move(int n, char source, char destination, char spare,int disc)
{
    if (n == 1)
    {
        printf("Moved %d from %c to %c\n",disc,source,destination);
    }
    else
    {
        move(n-1,source,spare,destination,disc-1);
        move(1,source,destination,spare,disc);
        move(n-1,spare,destination,source,disc-1);
    }
}