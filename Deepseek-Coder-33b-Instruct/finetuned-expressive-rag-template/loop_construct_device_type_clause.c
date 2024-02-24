#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:loop construct device_type clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_data, *device_data;
    int data_size = 100;
    int i;

    // Allocate memory on the host
    host_data = (int*)malloc(data_size * sizeof(int));
    if(host_data == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory on the host\n");
        return 1;
    }

    // Initialize host data
    for(i = 0; i < data_size; i++) {
        host_data[i] = i;
    }

    // Allocate memory on the device
    device_data = (int*)acc_malloc(data_size * sizeof(int));
    if(device_data == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory on the device\n");
        return 1;
    }

    // Copy data from host to device
    acc_memcpy_to_device(device_data, host_data, data_size * sizeof(int));

    // Execute the loop on the device
    #pragma acc parallel loop device_type(nvidia)
    for(i = 0; i < data_size; i++) {
        device_data[i] *= 2;
    }

    // Copy data from device to host
    acc_memcpy_from_device(host_data, device_data, data_size * sizeof(int));

    // Verify the results
    for(i = 0; i < data_size; i++) {
        if(host_data[i] != i * 2) {
            fprintf(stderr, "Error: Verification failed at index %d\n", i);
            err = 1;
            break;
        }
    }

    // Free memory
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