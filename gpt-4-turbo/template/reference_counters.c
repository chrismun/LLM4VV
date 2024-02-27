#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int size = 1024;
    int *host_array = (int*)malloc(size * sizeof(int));
    int *host_array_copy = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        host_array[i] = rand() / (RAND_MAX / 100);
        host_array_copy[i] = host_array[i];
    }

    #pragma acc enter data copyin(host_array[0:size])

    // Increment all elements to verify if they are correctly referenced
    #pragma acc parallel loop present(host_array[0:size])
    for (int i = 0; i < size; ++i){
        host_array[i] += 1;
    }

    // Copy data back to verify
    #pragma acc exit data copyout(host_array[0:size])

    // Verify the incremented values to ensure correct reference handling
    for (int i = 0; i < size; ++i){
        if ( host_array[i] != host_array_copy[i] + 1) {
            err += 1;
        }
    }

    free(host_array);
    free(host_array_copy);

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