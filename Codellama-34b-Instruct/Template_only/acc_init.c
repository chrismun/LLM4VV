c
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)acc_malloc(sizeof(int));
    int *b = (int *)acc_malloc(sizeof(int));

    // Initialize the data
    *a = 1;
    *b = 2;

    // Create an OpenACC region
    #pragma acc region
    {
        // Initialize the data in the region
        *a = 3;
        *b = 4;
    }

    // Check the data outside the region
    if (*a != 3 || *b != 4) {
        err = 1;
    }

    // Free the memory
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