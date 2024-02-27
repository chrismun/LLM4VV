#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int n = 1000;
    float *a, *result;

    a = (float*)malloc(n * sizeof(float));
    result = (float*)malloc(n * sizeof(float));

    // Initialize array with random values
    for(int i = 0; i < n; i++) {
        a[i] = (float)rand()/(float)(RAND_MAX);
        result[i] = 0.0f;
    }

    // Use OpenACC kernels construct to compute squares
#pragma acc kernels copyin(a[0:n]) copyout(result[0:n])
    for(int i = 0; i < n; i++){
        result[i] = a[i] * a[i];
    }

    // Verify results
    for(int i = 0; i < n; i++) {
        if(abs(result[i] - (a[i]*a[i])) > 1e-6) {
            err++;
        }
    }

    free(a);
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