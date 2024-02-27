#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#ifndef PRECISION
#define PRECISION 0.01
#endif

#ifndef SEED
#define SEED 12345
#endif

#ifndef N
#define N 1024
#endif

int test_enter_data(){
    int err = 0;
    srand(SEED);
    float *a = (float *)malloc(N * sizeof(float)); // Host array
    float *b = (float *)malloc(N * sizeof(float)); // Host array for validation

    // Initialize array 'a' with random numbers
    for (int i = 0; i < N; ++i){
        a[i] = rand() / (float)(RAND_MAX / 10);
    }

    // Use the enter data directive to create corresponding device array and copy data 'a' from host to device
    #pragma acc enter data copyin(a[0:N])

    // Perform computation on the device
    #pragma acc parallel loop copyout(b[0:N])
    for(int i = 0; i < N; i++){
        b[i] = a[i] * 2.0; // Example computation
    }

    // Verify b[i] is as expected
    for (int i = 0; i < N; ++i){
        if (fabs(b[i] - (a[i] * 2.0)) > PRECISION){
            err++;
        }
    }

    // Clean up device memory
    #pragma acc exit data delete(a[0:N])

    free(a);
    free(b);

    return err;
}

int main(){
    int failed = test_enter_data();
    if (failed) {
        printf("Test failed with %d errors.\n", failed);
        return 1;
    }
    printf("Test passed.\n");
    return 0;
}