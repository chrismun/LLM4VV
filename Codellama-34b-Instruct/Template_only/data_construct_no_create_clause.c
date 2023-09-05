#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data region with the no_create clause
    #pragma acc data no_create(a[0:n])
    {
        // Allocate memory for the data region
        a = (int*)malloc(n*sizeof(int));

        // Initialize the data region
        for (int i = 0; i < n; i++) {
            a[i] = i;
        }
    }

    // Check that the data region has not been created
    if (a == NULL) {
        err = 1;
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