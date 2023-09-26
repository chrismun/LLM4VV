#include "acc_testsuite.h"

//T1:data construct create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    unsigned int size = 1024;
    unsigned int *host_data = (unsigned int*)malloc(size * sizeof(unsigned int));
    unsigned int *device_data;
    // initialization of host_data array
    for (unsigned int i = 0; i < size; ++i) {
        host_data[i] = i;
    }
    // create space on device memory with initial values coming from host_data
    #pragma acc data create(device_data[0:size]) copyin(host_data[0:size])
    {
        #pragma acc parallel loop
        for (unsigned int i = 0; i < size; ++i) {
            device_data[i] = host_data[i] + 1;
        }
    }
    // copy results from device back to host_data
    #pragma acc update host(host_data[0:size])
    
    // check the results
    for (unsigned int i = 0; i < size; ++i) {
        if (host_data[i] != i + 1) {
            err = 1;
        }
    }

    free(host_data);
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    //T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}