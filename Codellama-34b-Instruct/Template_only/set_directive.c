#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)acc_malloc(sizeof(int) * 10);
    int *b = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize arrays
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Set the value of the first element of b to 10
    acc_set(b, 10, 1);

    // Check that the value of the first element of b is 10
    if (b[0] != 10) {
        err = 1;
    }

    // Set the value of the first element of a to 20
    acc_set(a, 20, 1);

    // Check that the value of the first element of a is 20
    if (a[0] != 20) {
        err = 1;
    }

    // Free memory
    acc_free(a);
    acc_free(b);

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