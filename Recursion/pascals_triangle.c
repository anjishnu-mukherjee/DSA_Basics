# include <stdio.h>

int pascal(int row, int col)
{
    if(col == 0 || col == row)
    {
        return 1;
    }
    return pascal(row-1,col) + pascal(row-1,col-1);
}

void printPascal(int n)
{
    for (int i =0;i< n ; i++)
    {
        for (int k =0; k < n -i;k++)
        {
            printf(" ");
        }

        for (int j = 0; j<=i; j++)
        {
            printf("%d ",pascal(i,j));
        }
        
        printf("\n");
    }
}

int main()
{
    int rows;
    printf("\nEnter the number of rows for Execution\n> ");
    scanf("%d",&rows);
    printPascal(rows);
    return 0;
}