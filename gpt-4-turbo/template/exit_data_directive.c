#include "acc_testsuite.h"
#ifndef T1
// T1:exit_data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a_host = (int *)malloc(size * sizeof(int));
    int *a_dev = NULL;

    // Initialize array
    for(int i = 0; i < size; ++i){
        a_host[i] = rand() % 100;
    }

    // Allocate and copy data to the device
    #pragma acc enter data copyin(a_host[0:size])
    a_dev = acc_deviceptr(a_host);

    // Modify the data on device
    #pragma acc parallel loop present(a_dev[0:size])
    for(int i = 0; i < size; ++i){
        a_dev[i] += 5;
    }

    // Use exit data to update the host array with device modifications and then deallocate device memory
    #pragma acc exit data copyout(a_host[0:size])

    // Verify modifications
    for(int i = 0; i < size; ++i){
        if(a_host[i] % 5 != 0){
            err++;
        }
    }

    free(a_host);
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