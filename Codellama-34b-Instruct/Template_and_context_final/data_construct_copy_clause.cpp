#include "acc_testsuite.h"

#ifndef T1
//T1:data construct copy clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    int* shared_mem = (int*)malloc(sizeof(int) * 10);

    // Initialize the shared memory region
    for (int i = 0; i < 10; i++) {
        shared_mem[i] = i;
    }

    // Create a copy of the shared memory region
    int* copy_mem = (int*)malloc(sizeof(int) * 10);

    // Copy the shared memory region to the copy
    for (int i = 0; i < 10; i++) {
        copy_mem[i] = shared_mem[i];
    }

    // Modify the copy of the shared memory region
    for (int i = 0; i < 10; i++) {
        copy_mem[i] += 1;
    }

    // Check that the shared memory region has not been modified
    for (int i = 0; i < 10; i++) {
        if (shared_mem[i] != i) {
            err = 1;
            break;
        }
    }

    // Free the copy of the shared memory region
    free(copy_mem);

    // Free the shared memory region
    free(shared_mem);

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