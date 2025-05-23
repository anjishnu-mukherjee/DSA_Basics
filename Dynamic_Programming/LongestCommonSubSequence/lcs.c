#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void readFromFile(char *str1, char *str2)
{
    FILE *file = fopen("stringinput.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%s", str1);
    fscanf(file, "%s", str2);
    fclose(file);
}

void printLCS(int B[MAX][MAX], char *str1, char *str2, int i, int j)
{
    if (i == 0 || j == 0)
        return;

    if (B[i][j] == 1)
    {
        printLCS(B, str1, str2, i - 1, j - 1);
        printf("%c", str1[i - 1]);
    }
    else if (B[i][j] == 2)
    {
        printLCS(B, str1, str2, i - 1, j);
    }
    else
    {
        printLCS(B, str1, str2, i, j - 1);
    }
}

int lcs(char *str1, char *str2, int **C)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int B[MAX][MAX];

    for (int i = 0; i <= len1; i++)
        C[i][0] = 0;
    for (int j = 0; j <= len2; j++)
        C[0][j] = 0;

    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                C[i][j] = C[i - 1][j - 1] + 1;
                B[i][j] = 1; // diagonal
            }
            else if (C[i - 1][j] >= C[i][j - 1])
            {
                C[i][j] = C[i - 1][j];
                B[i][j] = 2; // up
            }
            else
            {
                C[i][j] = C[i][j - 1];
                B[i][j] = 3; // left
            }
        }
    }

    printf("LCS: ");
    printLCS(B, str1, str2, len1, len2);
    printf("\n");
    return C[len1][len2];
}

int main()
{
    char *str1 = (char *)malloc(MAX * sizeof(char));
    char *str2 = (char *)malloc(MAX * sizeof(char));

    if (!str1 || !str2)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    readFromFile(str1, str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int **C = (int **)malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++)
        C[i] = (int *)malloc((len2 + 1) * sizeof(int));

    int length = lcs(str1, str2, C);
    printf("Length of LCS is %d\n", length);

    for (int i = 0; i <= len1; i++)
        free(C[i]);
    free(C);
    free(str1);
    free(str2);

    return 0;
}
