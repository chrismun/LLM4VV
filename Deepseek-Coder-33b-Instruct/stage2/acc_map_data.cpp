#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 100;
    int *host_data = (int*)malloc(size * sizeof(int));
    int *device_data;

    // Initialize host data
    for(int i = 0; i < size; i++) {
        host_data[i] = i;
    }

    // Map host data to device
    #pragma acc data copyin(host_data[0:size])
    {
        device_data = (int*)acc_malloc(size * sizeof(int));
        #pragma acc update device(host_data[0:size]) async(1)
        #pragma acc parallel loop async(2)
        for(int i = 0; i < size; i++) {
            device_data[i] = host_data[i];
        }
        #pragma acc wait
    }

    // Check if data is correctly mapped
    for(int i = 0; i < size; i++) {
        if(device_data[i] != host_data[i]) {
            err++;
        }
    }

    free(host_data);
    acc_free(device_data);

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