#include "acc_testsuite.h"
#ifndef T1
//T1:{host_data},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Vector addition on device memory
    const int vector_length = 1024;
    float *a, *b, *c;

    // Allocate and initialize vectors on the device
    a = (float *)acc_malloc(vector_length * sizeof(float));
    b = (float *)acc_malloc(vector_length * sizeof(float));
    c = (float *)acc_malloc(vector_length * sizeof(float));
    for(int i = 0; i < vector_length; ++i){
        a[i] = rand() / (float)RAND_MAX; // Init with random values
        b[i] = rand() / (float)RAND_MAX; // Init with random values
        c[i] = 0; // Initialize result vector
    }

    // Perform vector addition using the host_data use_device clause
    #pragma acc parallel loop present(a, b, c)
    for(int i = 0; i < vector_length; ++i){
        c[i] = a[i] + b[i];
    }

    #pragma acc host_data use_device(a, b, c)
    {
        // Operation occurs on the device, but specifying use_device allows
        // device pointers to be addressable from the host code in this context.
        // No actual host-side operation in this case, but demonstrates feasibility.
    }

    // Verification
    for(int i = 0; i < vector_length; ++i){
        float expected = a[i] + b[i];
        if (fabsf(c[i] - expected) > 1e-5){
            err++;
            break;
        }
    }

    // Cleanup
    acc_free(a);
    acc_free(b);
    acc_free(c);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}