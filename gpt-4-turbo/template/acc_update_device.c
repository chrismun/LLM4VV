#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int array_size = 1024;
    int *a_h, *a_d;
    a_h = (int *) malloc(array_size * sizeof(int));
    a_d = (int *) acc_malloc(array_size * sizeof(int));

    // Initialize array on host
    for (int i = 0; i < array_size; ++i){
        a_h[i] = rand() / (RAND_MAX / 100);
    }

    // Copy array to device
    acc_memcpy_to_device(a_d, a_h, array_size * sizeof(int));

    // Modify array on host
    for (int i = 0; i < array_size; ++i){
        a_h[i] += 10;
    }

    // Update device with modified array
    #pragma acc update device(a_h[0:array_size])

    // Execute a kernel to validate the update
    #pragma acc parallel loop present(a_d)
    for (int i = 0; i < array_size; ++i){
        a_d[i] += 1;
    }

    // Copy back the result to host to verify
    acc_memcpy_from_device(a_h, a_d, array_size * sizeof(int));

    // Verify the computation
    for (int i = 0; i < array_size; ++i){
        if(a_h[i] != (rand() / (RAND_MAX / 100) + 11)){
            err++;
            break;
        }
    }

    acc_free(a_d);
    free(a_h);
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