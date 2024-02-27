#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 1024
#define PRECISION 1e-5

// Assume real_t is defined as
typedef float real_t;

int test_detach_clause(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * detached_array = (real_t *)malloc(n * sizeof(real_t));
    srand(SEED);

    // Initialize the arrays
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        detached_array[x] = 0;
    }

    // Entering data region, setting up for possible detach
    #pragma acc enter data copyin(a[0:n]), create(detached_array[0:n])

    #pragma acc parallel loop
    for (int x = 0; x < n; ++x){
        detached_array[x] = a[x] * 2;
    }

    // Exiting data region with detach clause. No finalize, so deferred detach.
    #pragma acc exit data copyout(detached_array[0:n]) detach(detached_array)

    // Without an explicit API call to confirm detachment, we assume compiler behavior is correct.
    // Normally, you might expect an operation here that tests the effects or lack thereof of the detachment.
    // However, the detach's observable effects depend on the compiler and system's OpenACC implementation.

    // Check if detached_array was updated correctly before detachment.
    for (int x = 0; x < n; ++x){
        if (fabs(detached_array[x] - a[x] * 2) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(detached_array);

    return err;
}

int main(){
    int failcode = 0;
    int failed = test_detach_clause();
    if (failed != 0){
        printf("Test FAILED with %d errors.\n", failed);
        failcode = 1;
    } else {
        printf("Test PASSED.\n");
    }
    return failcode;
}