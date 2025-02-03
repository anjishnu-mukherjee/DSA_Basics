#include <stdio.h>
#include <stdlib.h>

typedef struct chess
{
    int queen;
}chessboard;

void initialse(chessboard ** A,int n)
{
    for (int i =0; i <n ;i++)
    {
        for ( int j = 0; j< n ;j++)
        {
            A[i][j].queen = 0; // no queen
        }
    }
}

void print_chessboard(chessboard** A,int n)
{
    for (int i =0; i <n ;i++)
    {
        for ( int j = 0; j< n ;j++)
        {
            if (A[i][j].queen == 0)
            {
                printf("X ");
            }
            else
            {
                printf("Q ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int is_safe(chessboard** A, int row, int col, int n)
{
    for (int i = 0; i< row; i++)
    {
        if(A[i][col].queen == 1)
            return 0;
    }

    for (int i = row,j = col; i>=0 && j>=0; i--,j--)
    {
        if (A[i][j].queen == 1)
            return 0;
    }
    
    for (int i = row,j=col; i>=0 && j<n;i--,j++)
    {
        if(A[i][j].queen == 1)
            return 0;
    }

    return 1;
}

int solve_chessboard(chessboard** A,int row,int n)
{
    if (row >= n)
    {
        print_chessboard(A,n);
        return 1;
    }

    int solutions = 0;

    for (int col = 0; col<n;col++)
    {
        if (is_safe(A,row,col,n))
        {
            A[row][col].queen = 1;

            solutions +=solve_chessboard(A,row+1,n);

            A[row][col].queen = 0; // Backtrack (Remove queen)
        }
    }
    return solutions;
}

int main()
{
    int n;
    printf("\nEnter the size of the chess board\n>");
    scanf("%d",&n);

    chessboard ** A = (chessboard**)malloc(n*sizeof(chessboard*));
    for (int i = 0; i< n;i++)
    {
        A[i] = (chessboard*)malloc(n*sizeof(chessboard));
    }

    initialse(A,n);

    printf("\nSolutions for %d-Queens:\n\n", n);
    int total_solutions = solve_chessboard(A, 0, n);
    printf("Total Solutions: %d\n", total_solutions);

    for (int i =0; i< n;i++)
    {
        free(A[i]);
    }
    free(A);
    return 0;
}