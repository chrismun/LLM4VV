#include "acc_testsuite.h"
#ifndef T1
// T1:{parallel},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int n = 1024;
    int *a_host = (int*)malloc(n * sizeof(int));

    // Initialize array
    for (int i = 0; i < n; ++i){
        a_host[i] = rand() % 100;
    }

    // Data allocation on the device
    #pragma acc enter data copyin(a_host[0:n])
    
    // Attempt to use the data with the present clause
    #pragma acc parallel loop present(a_host[0:n])
    for (int i = 0; i < n; ++i){
        a_host[i] += 1;
    }

    // Retrieve data back to host to verify correctness
    #pragma acc exit data copyout(a_host[0:n])

    // Verification
    for (int i = 0; i < n; ++i) {
        if (a_host[i] != (initial_value + 1)) {
            err += 1; // Error if data not incremented as expected
        }
    }

    free(a_host);
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