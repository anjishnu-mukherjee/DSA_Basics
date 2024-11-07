#include <stdio.h>
#include <stdlib.h>

typedef struct poly_temrs
{
    int coef;
    int exp_x;
    int exp_y;
}poly;

poly * addP(poly *A, poly *B, int n1, int n2);
poly * mulP(poly *A, poly *B, int n1, int n2);
void sort(poly* A, int n);
void itself(poly* A, int *n);
int k=0,l=0;

int main()
{   
    int n1,n2;

    printf("Enter the terms of the first polynomial\n>");
    scanf("%d",&n1);
    printf("Enter the terms of the second polynomial\n>");
    scanf("%d",&n2);

    poly* A = (poly*)malloc(n1*sizeof(poly));
    poly* B= (poly*)malloc(n2*sizeof(poly));

    printf("Enter the elements of the first polynomial\n");
    for (int i = 0; i<n1; i++)
    {
        printf("Enter the coef: ");
        scanf("%d",&A[i].coef);
        printf("Enter the exponential of x: ");
        scanf("%d",&A[i].exp_x);
        printf("Enter the exponential of y: ");
        scanf("%d",&A[i].exp_y);
    }

    printf("Enter the elements of the first polynomial\n");
    for (int i = 0; i<n2; i++)
    {
        printf("Enter the coef: ");
        scanf("%d",&B[i].coef);
        printf("Enter the exponential of x: ");
        scanf("%d",&B[i].exp_x);
        printf("Enter the exponential of y: ");
        scanf("%d",&B[i].exp_y);
    }

    sort(A,n1);
    sort(B,n2);

    poly * res = addP(A,B,n1,n2);
    printf("\nThe Addition is: \n");
    for (int i =0 ; i < k ; i++)
    {
        printf("%dx%dy%d ",res[i].coef,res[i].exp_x,res[i].exp_y);
    }

    poly *pdt = mulP(A,B,n1,n2);
    itself(pdt,&l);
    printf("\nThe Multiplication is: \n");
    for (int i =0 ; i < l ; i++)
    {
        printf("%dx%dy%d ",pdt[i].coef,pdt[i].exp_x,pdt[i].exp_y);
    }

    free(A);
    free(B);
    free(res);
    free(pdt);  
}

poly * addP(poly *A, poly *B, int n1, int n2)
{
    poly * res = (poly*)malloc((n1+n2)*sizeof(poly));
    int i,j;
    for (i =0,j=0,k=0;i<n1 && j<n2;)
    {
        if (A[i].exp_x == B[j].exp_x && A[i].exp_y == B[j].exp_y)
        {
            if ((A[i].coef + B[j].coef) != 0)
            {
                res[k].coef = A[i].coef + B[j].coef;
                res[k].exp_x = A[i].exp_x;
                res[k].exp_y = A[i].exp_y;
                k++;
            }
            i++;
            j++;
        }
        else if ((A[i].exp_x < B[j].exp_x) || (A[i].exp_x == B[j].exp_x && A[i].exp_y < B[j].exp_y))
        {
            res[k]=A[i];
            k++;
            i++;
        }
        else 
        {
            res[k]=B[j];
            k++;
            j++;
        }
    }

    if (i<n1)
    {
        while (i<n1)
        {
            res[k]=A[i];
            i++;
            k++;
        }
    }
    else if (j<n2)
    {
        while (j<n2)
        { 
            res[k] = B[j];
            j++;
            k++;
        }
    }
    return res;
}

poly * mulP(poly *A, poly *B, int n1, int n2)
{
    poly *pdt = (poly *)malloc((n1*n2)*sizeof(poly));
    int i, j;
    for (i =0; i <n1;i++)
    {
        for(j=0;j<n2;j++)
        {
            if ((A[i].exp_x + B[j].exp_x != 0) || (A[i].exp_y + B[j].exp_y != 0))
            {
                pdt[l].coef=A[i].coef * B[j].coef;
                pdt[l].exp_x=A[i].exp_x + B[j].exp_x;
                pdt[l].exp_y=A[i].exp_y + B[j].exp_y;
                l++;
            }
        }
    }

    return pdt;
}

void sort(poly* A, int n)
{
    poly temp;
    for (int i = n; i > 1; i--)
    {
        for (int j = 0; j < i - 1; j++)
        {
            if (A[j].exp_x > A[j+1].exp_x)
            {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
            else if (A[j].exp_x == A[j+1].exp_x)
            {
                if (A[j].exp_y > A[j+1].exp_y)
                {
                    temp = A[j];
                    A[j] = A[j+1];
                    A[j+1] = temp;
                }
            }
        }
    }
}


void itself(poly* A, int *n)
{
    int i,j,m;
    for (i = 0; i < *n; i++) 
    {
        for (j = i + 1; j < *n; ) 
        {  
            if (A[i].exp_x == A[j].exp_x && A[i].exp_y == A[j].exp_y) 
            {
                A[i].coef += A[j].coef;
                
                for (m = j; m < *n - 1; m++) 
                {
                    A[m] = A[m + 1];
                }
                (*n)--; 
            } 
            else 
            {
                j++; 
            }
        }
    }
}