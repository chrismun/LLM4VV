c
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)acc_malloc(sizeof(int));
    int *b = (int *)acc_malloc(sizeof(int));
    int *c = (int *)acc_malloc(sizeof(int));

    // Initialize data
    *a = 1;
    *b = 2;
    *c = 3;

    // Detach data
    acc_detach(a);
    acc_detach(b);
    acc_detach(c);

    // Verify data
    if (*a != 1 || *b != 2 || *c != 3) {
        err = 1;
    }

    // Free memory
    acc_free(a);
    acc_free(b);
    acc_free(c);

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