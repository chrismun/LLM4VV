#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdbool.h>

#ifndef T1
/*
 * Test the 'if clause' of the kernels construct.
 */
int test1() {
    int err = 0;
    bool cond = false;  // we will alternate this condition
    float *a, *b, *c;
    int n = 10000;

    a = (float*) malloc(n*sizeof(float));
    b = (float*) malloc(n*sizeof(float));
    c = (float*) malloc(n*sizeof(float));

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = (float) rand() / RAND_MAX;
        b[i] = (float) rand() / RAND_MAX;
        c[i] = 0;
    }    

    #pragma acc enter data copyin(a[0:n], b[0:n]) copyout(c[0:n])

    #pragma acc kernels if (cond)
    for(int i = 0; i < n; i++)
        c[i] = a[i] + b[i];
   
    #pragma acc exit data copyout(c[0:n])
   
    // Verification
    for(int i=0; i<n; i++) {
        if (c[i] != a[i] + b[i]) {
            err = 1;
            break;
        }
    }

    // Free memory
    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main() {
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