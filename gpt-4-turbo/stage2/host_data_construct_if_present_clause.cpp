#include <iostream>
#include <cstdlib>
#include <openacc.h>

#ifndef T1
// T1:host_data construct if_present clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(42); // using a fixed seed for reproducibility

    const int size = 1024;
    float *data = (float *)malloc(size * sizeof(float));
    float *device_ptr = nullptr;

    // Optionally, allocate on the device and copy data to simulate "present" data
    if (rand() % 2) { // Randomly decide if data should be on the device
        device_ptr = (float *)acc_malloc(size * sizeof(float));
        acc_memcpy_to_device(device_ptr, data, size * sizeof(float));
    }

    // Use host_data construct with if_present clause
    #pragma acc host_data use_device(data) if_present
    {
        if (acc_is_present(data, size * sizeof(float)) != (device_ptr != nullptr)) {
            err++;
        }
    }

    // Cleanup
    if (device_ptr) {
        acc_free(device_ptr);
    }
    free(data);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    const int NUM_TEST_CALLS = 10;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}