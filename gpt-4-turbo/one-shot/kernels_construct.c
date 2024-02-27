#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEED 12345
#define N 1000
#define PRECISION 0.00001

typedef float real_t; // Define real_t as per your requirement, here we use float for simplicity

int test_kernels_construct(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(N * sizeof(real_t));
    real_t *b = (real_t *)malloc(N * sizeof(real_t));

    // Initialize array `a` with random values and `b` to 0
    for (int i = 0; i < N; ++i){
        a[i] = rand() / (real_t)(RAND_MAX / 10);
        b[i] = 0;
    }

    // Use OpenACC kernels directive to perform parallel copy
    #pragma acc kernels copyin(a[0:N]) copyout(b[0:N])
    for (int i = 0; i < N; ++i){
        b[i] = a[i];
    }

    // Verify the operation
    for (int i = 0; i < N; ++i){
        if (fabs(b[i] - a[i]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);
    return err;
}

int main(){
    int failcode = 0;
    
    if (test_kernels_construct() != 0){
        failcode = 1;
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }

    return failcode;
}