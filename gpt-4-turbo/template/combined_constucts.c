#include "acc_testsuite.h"
#ifndef T1
//T1:combined-constructs,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    float *a = (float*)malloc(size * sizeof(float));
    float *b = (float*)malloc(size * sizeof(float));
    float *c = (float*)malloc(size * sizeof(float));
    float *result = (float*)malloc(size * sizeof(float));

    // Initialize arrays with random data
    for (int i = 0; i < size; ++i){
        a[i] = (float)rand()/RAND_MAX;
        b[i] = (float)rand()/RAND_MAX;
        c[i] = 0.0f; // Initialize output array
    }

    #pragma acc kernels copyin(a[0:size], b[0:size]) copyout(c[0:size])
    for (int i = 0; i < size; ++i) {
        c[i] = a[i] + b[i];
    }

    // Verification of results
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
        if (fabsf(result[i] - c[i]) > 1e-5) {
            err++;
        }
    }

    free(a);
    free(b);
    free(c);
    free(result);
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