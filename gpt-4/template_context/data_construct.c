#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Number of elements
#define N 1000000

int main() {
    int i, error_count = 0;
    float *a, *b, *c;

    a = (float*) malloc (N * sizeof(float));
    b = (float*) malloc (N * sizeof(float));
    c = (float*) malloc (N * sizeof(float));

    // Initialize vectors with some values
    for(i = 0; i < N; i++ ) {
        a[i] = (float) i;
        b[i] = (float) (i * 2);
        c[i] = 0.0f;
    }

    // Copying data from CPU to GPU before computation
    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc kernels
        for(i = 0; i < N; i++ ) {
            c[i] = a[i] + b[i];
        }
    }
    // Data is automatically copied back from GPU to CPU after computation

    // Validation
    for(i = 0; i < N; i++ ) {
        if(c[i] != a[i] + b[i]) {
            error_count++;
        }
    }

    if(error_count > 0) {
        printf("Validation failed! - Found %d errors.\n", error_count);
    } else {
        printf("Validation passed!\n");
    }

    // Release the vectors
    free(a);
    free(b);
    free(c);

    return 0;
}