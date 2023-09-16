#include "acc_testsuite.h"
#ifndef T1
//T1:acc deviceptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_array = (int*)malloc(n * sizeof(int));

    // Generate random values
    for (int i = 0; i < n; i++) {
        host_array[i] = rand() % 10;
    }

    int *device_array;
    int *copy_array = (int*)malloc(n * sizeof(int));

    #pragma acc data copyin(host_array[0:n]) copyout(device_array[0:n])
    {
        #pragma acc parallel loop present(host_array, device_array)
        for (int i = 0; i < n; i++) {
            device_array[i] = host_array[i];
        }
    }

    #pragma acc update host(copy_array[0:n]) async(1)
    #pragma acc wait(1)

    for (int i = 0; i < n; i++) {
        if (copy_array[i] != host_array[i]) {
            err = 1;
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