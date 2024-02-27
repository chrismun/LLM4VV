#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1:acc_attach,V:2.7-3.3
int test_acc_attach_detach() {
    int err = 0;
    const int data_size = 1024;
    int *host_data = (int *)malloc(data_size * sizeof(int));
    int *device_data;

    // Populate host data for testing
    for(int i = 0; i < data_size; ++i){
        host_data[i] = rand() % 100;
    }

    // Allocate device memory
    device_data = (int *)acc_malloc(data_size * sizeof(int));
    if (device_data == NULL) {
        printf("Error: Failed to allocate device memory.\n");
        free(host_data);
        return 1; // Indicates failure due to memory allocation issue
    }

    // Attempt to use acc_attach - note, a real program might use more sophisticated checks
    acc_attach((void **)&host_data);

    // Copy data to device to verify acc_attach functionality
    #pragma acc parallel loop copyout(host_data[0:data_size])
    for (int i = 0; i < data_size; ++i) {
        device_data[i] = host_data[i];
    }

    // Attempt to use acc_detach
    acc_detach((void **)&host_data);

    // Validate by copying back and checking a few values
    #pragma acc update host(device_data[0:data_size])
    for (int i = 0; i < 5; ++i) {
        if (device_data[i] != host_data[i]) {
            err += 1; // Error count increments if values mismatch
        }
    }

    acc_free(device_data);
    free(host_data);

    return err;
}
#endif

int main() {
    int failcode = 0;

#ifndef T1
    if(test_acc_attach_detach() != 0){
        failcode |= 1; // Set bit 0 if there's an error
    }
#endif

    return failcode;
}