#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


void print_optimal_parens(int **s, int i, int j)
{
    if (i == j)
    {
        printf("A%d", i + 1); 
    }
    else
    {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}


int matrix_chain_order(int p[], int n)
{
    
    int **m = (int **)malloc(n * sizeof(int *));
    int **s = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
    {
        m[i] = (int *)malloc(n * sizeof(int));
        s[i] = (int *)malloc(n * sizeof(int));
    }

    
    for (int i = 0; i < n; i++)
    {
        m[i][i] = 0;
    }

    
    for (int L = 2; L <= n; L++)
    {
        for (int i = 0; i < n - L + 1; i++)
        {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    
    printf("\nOptimal Parenthesization: ");
    print_optimal_parens(s, 0, n - 1);
    printf("\n");

    int result = m[0][n - 1];

    
    for (int i = 0; i < n; i++)
    {
        free(m[i]);
        free(s[i]);
    }
    free(m);
    free(s);

    return result;
}

int main()
{
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    if (n < 1)
    {
        printf("Number of matrices must be at least 1.\n");
        return 1;
    }

    int *p = (int *)malloc((n + 1) * sizeof(int));

    printf("\nEnter the dimensions of the matrices:\n");
    printf("Note: For matrices A1, A2, ..., An,\nEnter dimensions as d0, d1, d2, ..., dn\n");
    printf("where Ai has dimensions di-1 x di\n\n");

    for (int i = 0; i <= n; i++)
    {
        printf("Enter dimension d%d: ", i);
        scanf("%d", &p[i]);
    }

    printf("\nCalculating optimal matrix chain multiplication...\n");
    int min_multiplications = matrix_chain_order(p, n);
    printf("Minimum number of multiplications is %d\n", min_multiplications);

    free(p);
    return 0;
}