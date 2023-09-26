#include "acc_testsuite.h"
#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));
    
    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // OpenACC update self
    #pragma acc enter data copyin(a[0:n], b[0:n])
    
    // Perform calculations on GPU
    #pragma acc kernels
    for (int i = 0; i < n; i++) {
        a[i] += b[i];
    }

    // OpenACC update self
    #pragma acc exit data copyout(a[0:n])
    
    // Validate the results
    for (int i = 0; i < n; i++) {
        if (a[i] != 2 * b[i]) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;

#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }

    if (failed != 0) {
        failcode |= (1 << 0);
    }
#endif

    return failcode;
}