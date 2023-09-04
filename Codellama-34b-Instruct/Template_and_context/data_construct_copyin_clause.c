#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a shared array
    int *shared_array = (int *)malloc(10 * sizeof(int));

    // Create a non-shared array
    int *non_shared_array = (int *)malloc(10 * sizeof(int));

    // Initialize the shared array with random values
    for (int i = 0; i < 10; i++) {
        shared_array[i] = rand();
    }

    // Initialize the non-shared array with random values
    for (int i = 0; i < 10; i++) {
        non_shared_array[i] = rand();
    }

    // Copy the non-shared array to the shared array using the copyin clause
    #pragma acc enter data copyin(non_shared_array[:10])

    // Check that the shared array has the same values as the non-shared array
    for (int i = 0; i < 10; i++) {
        if (shared_array[i] != non_shared_array[i]) {
            err = 1;
            break;
        }
    }

    // Free the arrays
    free(shared_array);
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