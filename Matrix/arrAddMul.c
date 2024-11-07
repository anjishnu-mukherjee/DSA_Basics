#include <stdio.h>
#include <stdlib.h>

 
void allocateArray(int ***array, int rows, int cols) 
{
    *array = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) 
    {
        (*array)[i] = (int *)malloc(cols * sizeof(int));
    }
}

void freeArray(int **array, int rows) 
{
    for (int i = 0; i < rows; i++) 
    {
        free(array[i]);
    }
    free(array);
}

void inputArray(int **array, int rows, int cols) 
{
    printf("Enter elements of the array:\n");
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &array[i][j]);
        }
    }
}

void printArray(int **array, int rows, int cols) 
{
    printf("Array elements:\n");
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

void addArrays(int **array1, int **array2, int **result, int rows, int cols) 
{
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            result[i][j] = array1[i][j] + array2[i][j];
        }
    }
}

void multiplyArrays(int **array1, int **array2, int **result, int rows1, int cols1, int rows2, int cols2) 
{
    if (cols1 != rows2) 
    {
        printf("Matrix multiplication not possible: Number of columns of first matrix must be equal to number of rows of second matrix.\n");
        return;
    }
    for (int i = 0; i < rows1; i++) 
    {
        for (int j = 0; j < cols2; j++) 
        {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++) 
            {
                result[i][j] += array1[i][k] * array2[k][j];
            }
        }
    }
}

int main() 
{
    int **array1, **array2, **result;
    int rows1, cols1, rows2, cols2;
    int choice;

    printf("Enter rows and columns for the first array: ");
    scanf("%d %d", &rows1, &cols1);
    allocateArray(&array1, rows1, cols1);
    inputArray(array1, rows1, cols1);

    printf("Enter rows and columns for the second array: ");
    scanf("%d %d", &rows2, &cols2);
    allocateArray(&array2, rows2, cols2);
    inputArray(array2, rows2, cols2);


    if (rows1 == rows2 && cols1 == cols2) 
    {
        allocateArray(&result, rows1, cols1);
    } else if (cols1 == rows2) 
    {
        allocateArray(&result, rows1, cols2);
    } else 
    {
        printf("The operation cannot be performed with the given dimensions.\n");
        freeArray(array1, rows1);
        freeArray(array2, rows2);
        return 1;
    }

    printf("Choose an operation:\n1. Add\n2. Multiply\n");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            if (rows1 == rows2 && cols1 == cols2) 
            {
                addArrays(array1, array2, result, rows1, cols1);
                printf("Result of addition:\n");
                printArray(result, rows1, cols1);
            } else 
            {
                printf("Addition not possible with these dimensions.\n");
            }
            break;
        case 2:
            if (cols1 == rows2) 
            {
                multiplyArrays(array1, array2, result, rows1, cols1, rows2, cols2);
                printf("Result of multiplication:\n");
                printArray(result, rows1, cols2);
            } else 
            {
                printf("Multiplication not possible with these dimensions.\n");
            }
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    
    freeArray(array1, rows1);
    freeArray(array2, rows2);
    freeArray(result, (choice == 2 && cols1 == rows2) ? rows1 : (rows1 == rows2 && cols1 == cols2) ? rows1 : 0);

    return 0;
}
