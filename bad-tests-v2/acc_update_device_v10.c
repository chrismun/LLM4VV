#include "acc_testsuite.h"
#ifndef T1
//T1:acc update device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array = (int*)malloc(N * sizeof(int));

    // Initialize host_array with random values
    for (int i = 0; i < N; ++i){
        host_array[i] = rand() % 100;
    }
    
    // Allocate and copy host_array to device_array
    #pragma acc data create(device_array[0:N])
    {
        #pragma acc update device(device_array[0:N])
    }

    // Verify that device_array holds the same values as host_array
    for (int i = 0; i < N; ++i){
        if (host_array[i] != device_array[i]){
            err = 1;
            break;
        }
    }

    free(host_array);
    free(device_array);

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