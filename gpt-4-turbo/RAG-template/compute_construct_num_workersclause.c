#include "acc_testsuite.h"
#ifndef T1
//T1:{feature}, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int array_size = 10000;  // Array size should be large enough for the test
    int *a = (int*)malloc(array_size * sizeof(int));  // Allocate memory for the test array
    for (int i = 0; i < array_size; ++i){
        a[i] = 0;  // Initialize array values to 0
    }
    int num_workers_requested = 4;  // Example number of workers to request.
    
    #pragma acc parallel num_workers(num_workers_requested) copy(a[0:array_size])
    {
        #pragma acc loop independent
        for (int i = 0; i < array_size; ++i){
            a[i] += 1;  // Each worker increments part of the array
        }
    }
    // Check results. This approach is simplistic and assumes uniform distribution of work,
    // which might not always be the case depending on the compiler/runtime specifics.
    int count = 0;
    for (int i = 0; i < array_size; ++i){
        if (a[i] == 1){
            count += 1;
        }
    }
    // If the `num_workers` clause worked, `count` should be approximately equal to `array_size`.
    // Depending on distribution and hardware, some deviation might be acceptable.
    if (count != array_size){
        err += 1;  // Non-zero error indicates a potential issue or discrepancy.
    }

    free(a);
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