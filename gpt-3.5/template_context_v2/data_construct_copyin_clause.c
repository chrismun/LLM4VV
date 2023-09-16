#include "acc_testsuite.h"
#ifndef T1
//T1:data construct copyin clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int* host_ptr = (int*)malloc(N * sizeof(int));
    int* device_ptr;

    // Initialize host_ptr with random values
    for (int i = 0; i < N; ++i) {
        host_ptr[i] = rand() % 100;
    }

    // Allocate memory on the device
    #pragma acc data copyin(host_ptr[0:N])
    {
        #pragma acc parallel present(host_ptr[0:N])
        {
            // Access host_ptr on the device
            #pragma acc loop
            for (int i = 0; i < N; ++i) {
                host_ptr[i]++;
            }
        } // end parallel region

        // Allocate memory on the device for device_ptr
        #pragma acc host_data use_device(device_ptr)
        {
            device_ptr = (int*)acc_malloc(N * sizeof(int));
        }

        // Copy data from host_ptr to device_ptr
        #pragma acc parallel present(host_ptr[0:N]) copyout(device_ptr[0:N])
        {
            #pragma acc loop
            for (int i = 0; i < N; ++i) {
                device_ptr[i] = host_ptr[i];
            }
        } // end parallel region

        // Verify data on the host and device
        #pragma acc host_data use_device(device_ptr)
        {
            #pragma acc parallel present(host_ptr[0:N], device_ptr[0:N])
            {
                // Access host_ptr and device_ptr on the device
                #pragma acc loop
                for (int i = 0; i < N; ++i) {
                    if (host_ptr[i] != device_ptr[i]) {
                        err = 1;
                        break;
                    }
                }
            } // end parallel region
        }

        // Free device memory
        #pragma acc host_data use_device(device_ptr)
        {
            acc_free(device_ptr);
        }
    } // end data region

    free(host_ptr);

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