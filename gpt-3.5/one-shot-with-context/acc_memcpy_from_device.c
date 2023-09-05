#include "acc_testsuite.h"

#ifndef T1
// T1: async, data, device
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate device memory
    real_t *dev_data = acc_malloc(N * sizeof(real_t));
    if (!dev_data) {
        return 1;
    }

    // Initialize device data
    #pragma acc parallel loop present(dev_data)
    for (int i = 0; i < N; ++i) {
        dev_data[i] = i;
    }

    // Allocate host memory
    real_t *host_data = (real_t *)malloc(N * sizeof(real_t));
    if (!host_data) {
        acc_free(dev_data);
        return 1;
    }

    // Perform asynchronous copy from device to host
    #pragma acc data present(dev_data)
    {
        #pragma acc host_data use_device(host_data)
        {
            acc_memcpy_from_device_async(host_data, dev_data, N * sizeof(real_t), acc_async_sync);
        }
    }

    // Validate data
    for (int i = 0; i < N; ++i) {
        if (host_data[i] != i) {
            err = 1;
            break;
        }
    }

    // Free memory
    free(host_data);
    acc_free(dev_data);

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