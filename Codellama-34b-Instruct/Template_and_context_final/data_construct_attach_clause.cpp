#include "acc_testsuite.h"
#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a pointer to a shared memory region
    int* shared_ptr = (int*)malloc(sizeof(int));

    // Create a pointer to a non-shared memory region
    int* non_shared_ptr = (int*)malloc(sizeof(int));

    // Attach the non-shared memory region to the shared memory region
    #pragma acc attach(non_shared_ptr, shared_ptr)

    // Perform some operations on the shared memory region
    #pragma acc parallel
    {
        // ...
    }

    // Detach the non-shared memory region from the shared memory region
    #pragma acc detach(non_shared_ptr, shared_ptr)

    // Free the memory
    free(shared_ptr);
    free(non_shared_ptr);

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