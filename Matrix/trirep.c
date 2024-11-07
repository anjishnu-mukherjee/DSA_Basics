#include <stdio.h>
#include <stdlib.h>

typedef struct triplet_representation
{
    int r;
    int c;
    int val;
} trm;

void matadd(trm* mat1, trm* mat2, trm* res);
void matmul(trm* mat1, trm* mat2, trm* res);
void print_matrix(trm* mat);

int main()
{
    int row, col, nz1, nz2, i;

    printf("Enter the number of rows: ");
    scanf("%d", &row);
    printf("Enter the number of columns: ");
    scanf("%d", &col);
    printf("Enter the number of non-zero elements for matrix 1: ");
    scanf("%d", &nz1);
    printf("Enter the number of non-zero elements for matrix 2: ");
    scanf("%d", &nz2);

    if (row == 0 || col == 0 || nz1 == 0 || nz2 == 0)
    {
        printf("No elements stored!\n");
        return 1;
    }

    if ( nz1 > (row*col)/2.0 || nz2 > (row*col)/2.0)
    {
        printf("Condition Not Matched for Triplet Representation to be done!\n");
        return 2;
    }

    trm *mat1 = (trm *)malloc((nz1 + 1) * sizeof(trm));
    trm *mat2 = (trm *)malloc((nz2 + 1) * sizeof(trm));

    mat1[0].r = row;
    mat1[0].c = col;
    mat1[0].val = nz1;

    mat2[0].r = row;
    mat2[0].c = col;
    mat2[0].val = nz2;

    printf("Enter the non-zero elements for matrix 1:\n");
    for (i = 1; i <= nz1; i++)
    {
        printf("Element %d:\n", i);
        printf("Enter the row number: ");
        scanf("%d", &mat1[i].r);
        printf("Enter the column number: ");
        scanf("%d", &mat1[i].c);
        printf("Enter the value: ");
        scanf("%d", &mat1[i].val);
    }

    printf("Enter the non-zero elements for matrix 2:\n");
    for (i = 1; i <= nz2; i++)
    {
        printf("Element %d:\n", i);
        printf("Enter the row number: ");
        scanf("%d", &mat2[i].r);
        printf("Enter the column number: ");
        scanf("%d", &mat2[i].c);
        printf("Enter the value: ");
        scanf("%d", &mat2[i].val);
    }

    printf("Matrix 1 in triplet representation:\n");
    print_matrix(mat1);

    printf("Matrix 2 in triplet representation:\n");
    print_matrix(mat2);

    // Matrix Addition
    trm* res_add = (trm*)malloc((nz1 + nz2 + 1) * sizeof(trm));
    matadd(mat1, mat2, res_add);
    printf("Resultant Matrix after Addition:\n");
    print_matrix(res_add);

    // Matrix Multiplication
    trm* res_mul = (trm*)malloc((nz1 * nz2 + 1) * sizeof(trm));
    matmul(mat1, mat2, res_mul);
    printf("Resultant Matrix after Multiplication:\n");
    print_matrix(res_mul);

    free(mat1);
    free(mat2);
    free(res_add);
    free(res_mul);

    return 0;
}

void matadd(trm* mat1, trm* mat2, trm* res)
{
    if (mat1[0].r != mat2[0].r || mat1[0].c != mat2[0].c)
    {
        printf("Matrices cannot be added as their dimensions do not match.\n");
        return;
    }

    int i = 1, j = 1, k = 1;
    while (i <= mat1[0].val && j <= mat2[0].val)
    {
        if (mat1[i].r < mat2[j].r || (mat1[i].r == mat2[j].r && mat1[i].c < mat2[j].c))
        {
            res[k++] = mat1[i++];
        }
        else if (mat2[j].r < mat1[i].r || (mat2[j].r == mat1[i].r && mat2[j].c < mat1[i].c))
        {
            res[k++] = mat2[j++];
        }
        else
        {
            res[k] = mat1[i];
            res[k++].val = mat1[i++].val + mat2[j++].val;
        }
    }

    while (i <= mat1[0].val) res[k++] = mat1[i++];
    while (j <= mat2[0].val) res[k++] = mat2[j++];

    res[0].r = mat1[0].r;
    res[0].c = mat1[0].c;
    res[0].val = k - 1;
}

void matmul(trm* mat1, trm* mat2, trm* res)
{
    if (mat1[0].c != mat2[0].r)
    {
        printf("Matrices cannot be multiplied as their dimensions do not match.\n");
        return;
    }

    res[0].r = mat1[0].r;
    res[0].c = mat2[0].c;
    res[0].val = 0;

    int k = 1;
    for (int i = 1; i <= mat1[0].val; i++)
    {
        for (int j = 1; j <= mat2[0].val; j++)
        {
            if (mat1[i].c == mat2[j].r)
            {
                res[k].r = mat1[i].r;
                res[k].c = mat2[j].c;
                res[k].val = mat1[i].val * mat2[j].val;
                k++;
            }
        }
    }

    res[0].val = k - 1;
}

void print_matrix(trm* mat)
{
    int i;
    printf("row\tcol\tval\n");
    for (i = 0; i <= mat[0].val; i++)
    {
        printf("%d\t%d\t%d\n", mat[i].r, mat[i].c, mat[i].val);
    }
}
