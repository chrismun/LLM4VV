#include "acc_testsuite.h"
#include <cmath>
#include <stdlib.h>

// Generate a precondition for this test
#define PRECONDITION (rand() % 2)

#ifndef T1
/*T1:kernels construct if clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    float *a, *b, *c;
    int n = 2048;
    srand(SEED);

    // Initialize data on host
    a = (float*)malloc(sizeof(float)*n);
    b = (float*)malloc(sizeof(float)*n);
    c = (float*)malloc(sizeof(float)*n);
    for(int i = 0; i < n; i++) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
    }

    // Compute on device if PRECONDITION is true, else compute on host
    #pragma acc kernels if(PRECONDITION) copy(a[0:n], b[0:n], c[0:n])
    {
        for(int i = 0; i < n; i++) {
            c[i] = a[i] + b[i];
        }
    }

    // Verification 
    for(int i = 0; i < n; i++) {
        float expected = a[i] + b[i];
        if(std::abs(c[i] - expected) > 0.0001) {
            err = 1;
            break;
        }
    }

    // Clean up
    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    srand(SEED);
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}