#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1: kernels construct async clause*/
int test1() {
    int err = 0;
    int n = 10000; // Vector size
    float* a = (float*) malloc(n * sizeof(float));
    float* b = (float*) malloc(n * sizeof(float));
    float* c = (float*) malloc(n * sizeof(float));
    float* d = (float*) malloc(n * sizeof(float));
    // Initialize vectors
    for(int i = 0; i < n; i++){
        a[i] = rand() / RAND_MAX;
        b[i] = rand() / RAND_MAX;
        c[i] = 0.0f;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc kernels async
        for(int i = 0; i<n; i++){
            c[i] = a[i] + b[i];
        }
        #pragma acc wait
    }

    // Check the result on the host side
    for(int i = 0; i < n; i++){
       d[i] = a[i] + b[i];
       if (abs(c[i] - d[i]) > 1e-5) {
            err = 1;
            break;
       }
    }
   
    free(a);
    free(b);
    free(c);
    free(d);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + 1;
    }
#endif
    return failcode;
}