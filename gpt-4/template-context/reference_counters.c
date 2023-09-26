#include "acc_testsuite.h"
#ifndef T1
//T1:reference counters, V:2.7-3.3
int test1(){
    int err = 0;
    int is_present;
    float* data_host = (float*)malloc(100 * sizeof(float));
    float* data_device;
    srand(SEED);

    #pragma acc enter data create(data_host[0:100])
    is_present = acc_is_present(data_host, 100 * sizeof(float));
    if(is_present != 1){
        err = 1;
    }

    #pragma acc update device(data_host[0:100])
    data_device = (float*) acc_deviceptr(data_host);

    // Checking if the data has copied to the device successfully
    if(data_device == NULL){
        err = 1;
    }

    #pragma acc update host(data_host[0:100])

    // Checking if the data is still in the device after data gate
    is_present = acc_is_present(data_host, 100 * sizeof(float));
    if(is_present != 1){
        err = 1;
    }

    #pragma acc exit data delete(data_host[0:100])
    is_present = acc_is_present(data_host, 100 * sizeof(float));
    if(is_present != 0){
        err = 1;
    }

    free(data_host);
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