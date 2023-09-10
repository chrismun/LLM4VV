#include "acc_testsuite.h"

#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data construct with a detach clause
    #pragma acc data detach(array)
    {
        // Allocate memory for the array
        int *array = (int *)malloc(sizeof(int) * 10);

        // Initialize the array with random values
        for (int i = 0; i < 10; i++) {
            array[i] = rand();
        }

        // Detach the array from the data construct
        #pragma acc detach(array)
    }

    // Check that the array is no longer attached to the data construct
    if (array != NULL) {
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