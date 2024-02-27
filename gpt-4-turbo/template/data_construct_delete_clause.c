#include "acc_testsuite.h"
#ifndef T1
// T1:{data},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    int *host_array = (int*)malloc(size * sizeof(int));

    // Initialize the array
    for (int i = 0; i < size; ++i){
        a[i] = rand() / (float)RAND_MAX * 100.0;
        host_array[i] = a[i];
    }

    // Using OpenACC to manage the data
    #pragma acc data copy(a[0:size])
    {
        // Modify the array on the device
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i){
            a[i] += 1;
        }

        // Delete the modified array from the device
        #pragma acc exit data delete(a[0:size])
    }

    // Verifying that the host array remains unchanged
    for (int i = 0; i < size; ++i){
        if (host_array[i] != a[i] - 1){
            err += 1;
            break;
        }
    }

    free(a);
    free(host_array);

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