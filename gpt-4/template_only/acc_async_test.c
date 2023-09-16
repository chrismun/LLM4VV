#include "acc_testsuite.h"
#ifndef T1
//T1:acc async test,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int array_size = 100;
    int *host_array = (int *)malloc(sizeof(int) * array_size);
    int *device_array = (int *)malloc(sizeof(int) * array_size);

    // Fill the host array with random data
    for(int i = 0; i < array_size; i++) {
        host_array[i] = rand();
    }

    // Here we copy the host array to the device array using an async kernel and then test if the async execution has completed
    #pragma acc enter data copyin(host_array[0:array_size]) create(device_array[0:array_size])
    #pragma acc parallel loop async
    for(int i = 0; i < array_size; i++) {
        device_array[i] = host_array[i];
    }

    // Check if the async execution has finished
    int async_val = acc_async_test_all();

    // If the async execution has not finished, this is an error
    if(async_val != 0){
        err = 1;
    }

    #pragma acc exit data delete(host_array[0:array_size]) copyout(device_array[0:array_size])
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