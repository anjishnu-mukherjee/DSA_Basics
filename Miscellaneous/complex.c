#include <stdio.h>
#include <stdlib.h>

typedef struct complex_number
{
    int real;
    int img;
}complex;

complex  addC(complex * a, int n);
complex  mulC(complex *a, int n);

int main()
{
    int n;
    complex sum, pdt;
    printf("Enter the number fo complex numbers you want to enter: ");
    scanf("%d",&n);
    complex * arr = (complex *)malloc(n*sizeof(complex));

    printf("Enter the complex numbers for addition and multiplication\n");
    for (int i = 0; i<n ;i++)
    {
        printf("Enter the real coef: ");
        scanf("%d",&arr[i].real);
        printf("Enter the imaginary coef: ");
        scanf("%d",&arr[i].img);
    }

    printf("Your Complex Numbers: \n");
    for (int i =0; i<n;i++)
    {
        if (arr[i].img <0)
        {
            printf("%d%di\n",arr[i].real,arr[i].img);
        }
        else
        {
            printf("%d+%di\n",arr[i].real,arr[i].img);
        }
    }

    sum = addC(arr, n);
    pdt = mulC(arr, n);

    printf("Sum of the complex numbers: ");
    if (sum.img <0)
    {
        printf("%d%di\n",sum.real,sum.img);
    }
    else
    {
        printf("%d+%di\n",sum.real,sum.img);
    }

    printf("Product of the complex numbers: ");
    if (pdt.img <0)
    {
        printf("%d%di\n",pdt.real,pdt.img);
    }
    else
    {
        printf("%d+%di\n",pdt.real,pdt.img);
    }
    
    free (arr);
}

complex addC(complex * a, int n)
{
    complex sum;
    sum.img =0;
    sum.real=0;
    for (int i=0;i<n;i++)
    {
        sum.real += a[i].real;
        sum.img += a[i].img;
    }
    return sum;
}

complex  mulC(complex *a, int n)
{
    complex pdt;
    int x=0, y=0;
    pdt.real = a[0].real;
    pdt.img =a[0].img;
    for (int i = 1; i<n;i++)
    {
        x = pdt.real*a[i].real - pdt.img*a[i].img;
        y = pdt.real*a[i].img + pdt.img*a[i].real;
        pdt.real = x;
        pdt.img =y;
    }
    return pdt;
}