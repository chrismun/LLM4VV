#include "acc_testsuite.h"

#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Create a shared memory array
    int *shared_array = (int *)acc_malloc(sizeof(int) * 10);

    // Create a non-shared memory array
    int *non_shared_array = (int *)malloc(sizeof(int) * 10);

    // Attach the non-shared array to the shared array
    acc_attach(non_shared_array, shared_array, sizeof(int) * 10);

    // Perform some operations on the shared array
    for (int i = 0; i < 10; i++) {
        shared_array[i] = i;
    }

    // Detach the non-shared array from the shared array
    acc_detach(non_shared_array, shared_array);

    // Check that the non-shared array is still accessible
    for (int i = 0; i < 10; i++) {
        if (non_shared_array[i] != i) {
            err++;
        }
    }

    // Free the memory
    acc_free(shared_array);
    free(non_shared_array);

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