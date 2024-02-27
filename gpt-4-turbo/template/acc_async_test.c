#include "acc_testsuite.h"
#ifndef T1
//T1:async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *host_array = (int*)malloc(size * sizeof(int));
    int *copy_array = (int*)malloc(size * sizeof(int));

    // Initialize the array with random data
    for (int i = 0; i < size; ++i){
        host_array[i] = rand() % 100;
        copy_array[i] = 0; // Ensure the copy_array is empty
    }

    // Test starts here
    #pragma acc data copyin(host_array[0:size]) copyout(copy_array[0:size])
    {
        #pragma acc parallel async
        for (int i = 0; i < size; ++i){
            copy_array[i] = host_array[i];
        }
    }
    #pragma acc wait

    // Verify the asynchronous copy
    for (int i = 0; i < size; ++i){
        if (host_array[i] != copy_array[i]){
            err += 1;
            break;
        }
    }    

    free(host_array);
    free(copy_array);

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