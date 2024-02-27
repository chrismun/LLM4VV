#include "acc_testsuite.h"
#ifndef T1
// T1:{host_data, if_present},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int array_size = 1024;
    float *host_array = (float*)malloc(array_size * sizeof(float));
    float *device_array = NULL;
    float sum = 0.f, expected_sum = 0.f;

    // Initialize host array
    for(int i = 0; i < array_size; ++i) {
        host_array[i] = (float)rand() / (float)(RAND_MAX);
        expected_sum += host_array[i];
    }

    // Trying to allocate and copy memory on the device
    #pragma acc enter data create(device_array[0:array_size]) if_present
    #pragma acc parallel loop copyin(host_array[0:array_size]) if_present
    for (int i = 0; i < array_size; i++) {
        #pragma acc host_data use_device(device_array) if_present
        {
            if (device_array != NULL) {
                device_array[i] = host_array[i];
            }
        }
    }
    
    // Sum up the values to check
    #pragma acc parallel loop reduction(+:sum) if_present
    for (int i = 0; i < array_size; i++) {
        #pragma acc host_data use_device(device_array) if_present
        {
            if (device_array != NULL) {
                sum += device_array[i];
            } else {
                sum += host_array[i];
            }
        }
    }
    
    // Cleaning up device memory
    #pragma acc exit data delete(device_array[0:array_size]) if_present

    // Check for correctness
    if (fabs(sum - expected_sum) > 1e-5) {
        err += 1;
    }

    free(host_array);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}