#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a global data access region
    #pragma acc data copy(a[0:n])
    {
        // Initialize the data
        for (int i = 0; i < n; i++) {
            a[i] = i;
        }

        // Perform a computation on the data
        #pragma acc parallel loop
        for (int i = 0; i < n; i++) {
            a[i] = a[i] + 1;
        }
    }

    // Check the results
    for (int i = 0; i < n; i++) {
        if (a[i] != i + 1) {
            err = 1;
            break;
        }
    }

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