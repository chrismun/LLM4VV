#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h> // Ensure this header is included for OpenACC directives

#ifndef T2
// T2:kernels,data,free,V:1.0-3.1

#define n 10000
#define PRECISION 0.001f
#define SEED 42

int test_acc_free(){
    int err = 0;
    srand(SEED);
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < n; ++i){
        a[i] = rand() / (float)(RAND_MAX / 10);
        b[i] = 0; // Will be overwritten by values from 'a' during the OpenACC operation
    }

    // Use OpenACC to perform operations and then free device memory associated with 'a'
    #pragma acc data copy(a[0:n])
    {
        #pragma acc kernels copyout(b[0:n])
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                b[i] = a[i];
            }
        }

        // Intentionally free device memory associated with 'a' to check proper memory management
        #pragma acc exit data delete(a[0:n])
    }

    // Verification
    for (int i = 0; i < n; ++i){
        if (fabsf(b[i] - a[i]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T2
    failed = test_acc_free();
    if (failed != 0){
        failcode = (1 << 1); // Error on test 2 (acc free)
    }
#endif

    if (failcode != 0) {
        printf("FAILED: Some tests on acc free did not pass. Fail code: %d\n", failcode);
    } else {
        printf("PASSED: All tests on acc free passed successfully.\n");
    }

    return failcode;
}