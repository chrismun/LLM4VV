#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create two arrays of random values
    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        a[i] = rand();
        b[i] = rand();
    }

    // Copy the values from a to b using the OpenACC memcpy directive
    #pragma acc memcpy(b, a, 10)

    // Check that the values in b are the same as the values in a
    for (int i = 0; i < 10; i++) {
        if (b[i] != a[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory allocated for the arrays
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