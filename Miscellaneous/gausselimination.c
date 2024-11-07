#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("This is Gaussian Elimination Algorithm for 3x3 Matrix\n");
    printf("Enter number of Variables: ");
    scanf("%d", &n);

    float *x = (float *)malloc(n * sizeof(float));
    float **a = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        a[i] = (float *)malloc((n + 1) * sizeof(float));
    }

    printf("Enter the coefficients and the equivalent value in the matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            scanf("%f", &a[i][j]);
        }
    }

    printf("Your Augmented Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            printf("%.2f ", a[i][j]);
        }
        printf("\n");
    }

    // Gaussian Elimination
    for (int j = 0; j < n; j++) {
        for (int i = j + 1; i < n; i++) {
            float r = a[i][j] / a[j][j];
            for (int k = j; k < n + 1; k++) {
                a[i][k] -= r * a[j][k];
            }
        }
    }

    // Backward Substitution
    for (int i = n - 1; i >= 0; i--) {
        float sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += a[i][j] * x[j];
        }
        x[i] = (a[i][n] - sum) / a[i][i];
    }

    printf("The solution is: \n");
    for (int i = 0; i < n; i++) {
        printf("x(%d) = %.2f\n", (i + 1), x[i]);
    }

    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    free(x);

    return 0;
}
