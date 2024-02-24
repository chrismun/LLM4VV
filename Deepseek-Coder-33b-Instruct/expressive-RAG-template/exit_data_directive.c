#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:exit data directive,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_data, *device_data;
    int size = 100;

    // Allocate memory on the host and device
    host_data = (int*)malloc(size * sizeof(int));
    device_data = (int*)acc_malloc(size * sizeof(int));

    // Initialize host data
    for (int i = 0; i < size; i++) {
        host_data[i] = i;
    }

    // Copy data to the device
    #pragma acc data copyin(host_data[:size]) copyout(device_data[:size])
    {
        // Copy data from the host to the device
        #pragma acc update device(host_data[:size])

        // Perform some computations on the device
        #pragma acc parallel loop
        for (int i = 0; i < size; i++) {
            device_data[i] = host_data[i] * 2;
        }

        // Copy data from the device to the host
        #pragma acc update self(device_data[:size])
    }

    // Verify the results
    for (int i = 0; i < size; i++) {
        if (device_data[i] != host_data[i] * 2) {
            err = 1;
            break;
        }
    }

    // Free the allocated memory
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
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}