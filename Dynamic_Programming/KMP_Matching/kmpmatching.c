#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void readfromfile(char *filename, char *text, char *pattern)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fscanf(fp, "%s", text);
    fscanf(fp, "%s", pattern);
    fclose(fp);
}

void computeprefix(char *pattern, int n, int *pi)
{
    pi[0] = 0;
    int k = 0;
    for (int i = 1; i < n; i++)
    {
        while (k > 0 && pattern[k] != pattern[i])
        {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[i])
        {
            k++;
        }
        pi[i] = k;
    }
}

void KMP(char *text, char* pattern, int n, int m)
{
    int pi[MAX];
    computeprefix(pattern, m, pi);

    int q = 0;
    for (int i =0; i<n; i++)
    {
        while(q>0 && pattern[q] != text[i])
        {
            q  = pi[q-1];
        }
        if (pattern[q] == text[i])
        {
            q++;
        }
        if (q == m)
        {
            printf("Pattern found at %d index\n",i-m+1);
            q = pi[q];
        }
    }
}

int main()
{
    char text[MAX];
    char pattern[MAX];

    readfromfile("inputstring.txt", text, pattern);
    int n = strlen(text);
    int m = strlen(pattern);

    printf("Text: %s, Size : %d\n", text, n);
    printf("Pattern: %s, Size : %d\n", pattern, m);
    KMP(text, pattern,n,m);
    return 0;
}