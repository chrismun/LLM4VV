#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

    // Define the number of elements in array
    const int N = 1000;

    // Allocate memory for device && host
    int* host_x = (int*)malloc(N*sizeof(int));
    int* device_x = (int*)acc_malloc(N*sizeof(int));

    // Initialize host data
    for(int i = 0; i < N; i++) {
        host_x[i] = i;
    }

    // Transfer data from host to device
    acc_memcpy_to_device(device_x, host_x, N*sizeof(int));

    int errors = 0;

    // Use host_data use_device to use device address
    #pragma acc host_data use_device(device_x)
    {
        // Map the host pointer to device pointer
        #pragma acc parallel loop present(device_x)
        for(int i = 0; i < N; i++) {
            device_x[i] = device_x[i] + 1;
        }
    }

    // Transfer back to host and check
    acc_memcpy_to_host(host_x, device_x, N*sizeof(int));

    for(int i = 0; i < N; i++) {
        if(host_x[i] != i+1) {
            errors++;
            printf("host_x[%d] = %d expected %d\n", i, host_x[i], i+1);
        }
    }

    if(errors == 0) {
        printf("OpenACC Test Passed\n");
    } else {
        printf("OpenACC Test Failed. Found %d errors.\n", errors);
    }

    return errors;
}