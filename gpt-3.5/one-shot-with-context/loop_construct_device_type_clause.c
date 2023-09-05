#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ompss.h"

void acc_loop_example(int n, double *a, double *b, double *c)
{
    int i;

    #pragma oss task for device_type(299)   <---- device_type clause
    for (i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main()
{
    int i;
    int n = 100;
    double *a = malloc(n * sizeof(double));
    double *b = malloc(n * sizeof(double));
    double *c = malloc(n * sizeof(double));

    for (i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 2 * i;
    }

    acc_loop_example(n, a, b, c);

    for (i = 0; i < n; i++) {
        printf("%lf ", c[i]);
    }

    free(a);
    free(b);
    free(c);

    return 0;