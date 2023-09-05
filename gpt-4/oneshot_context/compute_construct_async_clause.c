#include <stdio.h>
#include <openacc.h>

int main() {
    const int N = 1024;
    float *restrict a = (float*) malloc(N*sizeof(float));
    float *restrict b = (float*) malloc(N*sizeof(float));
    float *restrict c = (float*) malloc(N*sizeof(float));

    // Initialize a and b
    for(int i=0; i<N; i++) {
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }

    // Launch asynchronous kernel
    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc parallel loop async
        for(int i=0; i<N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    // Wait for completion
    acc_wait_all();

    // Print a few elements of c
    for(int i=0; i<10; i++) {
        printf("%f ", c[i]);
    }

    free(a);
    free(b);
    free(c);

    return 0;