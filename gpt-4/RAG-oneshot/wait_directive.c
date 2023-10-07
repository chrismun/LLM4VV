#include <stdio.h>
#include <openacc.h>
#define N 1000000

int main() {
    int i;
    float *a = (float *)malloc(N * sizeof(float));
    float *b = (float *)malloc(N * sizeof(float));
    float *c = (float *)malloc(N * sizeof(float));
  
    // Initialize the arrays
    for(i=0; i<N; i++){
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }

    #pragma acc parallel loop async(1)
    for(i=0; i<N; i++){
        a[i] = a[i] * 2.0f;
    }

    #pragma acc parallel loop async(2)
    for(i=0; i<N; i++){
        b[i] = b[i] * 3.0f;
    }

    // Wait for the completion of the async operations
    #pragma acc wait

    #pragma acc parallel loop
    for(i=0; i<N; i++){
        c[i] = a[i] + b[i];
    }

    acc_wait_all(); // Ensure all operations are complete

    // Check results
    float maxError = 0.0f;
    for(i=0; i<N; i++){
        maxError = fmax(maxError, fabs(c[i]-(5*i)));
    }
    printf("Max error: %f\n", maxError);

    free(a);
    free(b);
    free(c);
    return 0;
}