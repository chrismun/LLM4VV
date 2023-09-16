#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 1024
#define GPU_DEVICE 0

void evaluate_acc_wait() {
    int *data_host, *data_device;
    int i;

    // Allocate data on host and device
    data_host = (int*) malloc(SIZE * sizeof(int));
    data_device = (int*) acc_malloc(SIZE * sizeof(int));

    // Initialize data on host
    for (i = 0; i < SIZE; i++)
        data_host[i] = i;

    // Set device number
    acc_set_device_num(GPU_DEVICE, acc_device_nvidia);
    
    // Copy data from host to device asynchronously
    acc_memcpy_to_device_async(data_device, data_host, SIZE * sizeof(int), 0);

    // Wait for asynchronous copy to complete
    acc_wait(0);
  
    // Copy data back from device to host
    acc_memcpy_from_device(data_host, data_device, SIZE * sizeof(int));
  
    // Ensure the two copies match
    for (i = 0; i < SIZE; i++)
        assert(data_host[i] == i);

    // Free up memory
    free(data_host);
    acc_free(data_device);
}

int main() {
    evaluate_acc_wait();

    printf("Test executed successfully\n");

    return 0;
}