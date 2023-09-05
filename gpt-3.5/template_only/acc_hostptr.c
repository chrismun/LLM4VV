#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    
    int size = 100;
    int *hostData = (int*)malloc(size * sizeof(int));

    // Allocate device memory and copy data
    int *devData;
    #pragma acc enter data copyin(hostData[0:size]) create(devData[0:size])

    // Perform computation on the device using acc hostptr
    #pragma acc parallel loop present(hostData[0:size]) num_gangs(1) num_workers(1) vector_length(1) async(0)
    for (int i = 0; i < size; ++i) {
        #pragma acc hostptr(devData)
        {
            devData[i] = hostData[i] * 2;
        }
    }

    // Retrieve results from the device
    #pragma acc update self(hostData[0:size])

    // Verify correctness
    for (int i = 0; i < size; ++i) {
        if (hostData[i] != (i * 2)) {
            err = 1;
            break;
        }
    }

    // Deallocate memory
    #pragma acc exit data delete(hostData[0:size]) delete(devData[0:size])
    free(hostData);

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