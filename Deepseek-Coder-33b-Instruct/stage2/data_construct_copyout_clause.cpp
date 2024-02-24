#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:data construct copyout clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 100;
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data;

    // Initialize host data
    for(int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Allocate device memory
    device_data = (int*)acc_malloc(N * sizeof(int));

    // Copy data to device
    #pragma acc data copyin(host_data[:N]) copyout(device_data[:N])
    {
        // Perform computation on device
        #pragma acc kernels
        for(int i = 0; i < N; i++) {
            device_data[i] = host_data[i] * 2;
        }
    }

    // Check if data was correctly copied back to host
    for(int i = 0; i < N; i++) {
        if(device_data[i] != host_data[i] * 2) {
            err = 1;
            break;
        }
    }

    // Free device memory
    acc_free(device_data);
    free(host_data);

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