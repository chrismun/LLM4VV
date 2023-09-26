#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);

    // Initialize the arrays with random values
    for (int i = 0; i < 10; i++) {
        a[i] = rand();
        b[i] = rand();
    }

    // Use the use_device clause to tell the compiler to use the current device address of a and b
    #pragma acc host_data use_device(a, b)
    {
        // Perform some operations on the arrays
        for (int i = 0; i < 10; i++) {
            a[i] += b[i];
        }
    }

    // Check that the arrays have been updated correctly
    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i] + a[i]) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

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