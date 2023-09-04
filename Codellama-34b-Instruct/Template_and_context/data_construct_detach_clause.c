#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int *a, *b, *c;
    int n = 100;

    // Allocate memory for arrays
    a = (int*)malloc(n*sizeof(int));
    b = (int*)malloc(n*sizeof(int));
    c = (int*)malloc(n*sizeof(int));

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // Detach arrays from host memory
    #pragma acc detach(a, b, c)

    // Perform some computation on the arrays
    #pragma acc parallel loop
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }

    // Reattach arrays to host memory
    #pragma acc attach(a, b, c)

    // Print results
    for (int i = 0; i < n; i++) {
        printf("%d + %d = %d\n", a[i], b[i], c[i]);
    }

    // Free memory
    free(a);
    free(b);
    free(c);

    return 0;
}