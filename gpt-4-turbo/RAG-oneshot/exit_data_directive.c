#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 100
#define SEED 12345
#define PRECISION 1e-6

int test_exit_data_copyout(){
    int err = 0;
    float * a = (float *)malloc(n * sizeof(float));
    float * b = (float *)malloc(n * sizeof(float));

    // Initialize array a with random data
    srand(SEED);
    for (int i = 0; i < n; ++i){
        a[i] = (float)rand() / (float)(RAND_MAX / 10);
    }

    // Compute on device
    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels
        for (int i = 0; i < n; ++i){
            a[i] = a[i] * 2.0f; // Simple operation for testing
        }

        // Exit data directive with copyout
        #pragma acc exit data copyout(a[0:n])
    }

    // Verification
    for (int i = 0; i < n; ++i){
        if (fabs(a[i] - (float)rand() / (float)(RAND_MAX / 10) * 2.0f) > PRECISION){
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}

int main(){
    int failed = test_exit_data_copyout();
    if (failed > 0){
        printf("TEST FAILED: %d errors.\n", failed);
    } else {
        printf("TEST PASSED.\n");
    }
    return failed;
}