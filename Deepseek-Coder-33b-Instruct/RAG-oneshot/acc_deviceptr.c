#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    const int n = 100;
    int *host_array = (int*)malloc(n * sizeof(int));
    int *device_array;

    // Initialize host array
    for(int i = 0; i < n; i++) {
        host_array[i] = i;
    }

    // Allocate device memory and copy host array to device
    #pragma acc enter data create(device_array[0:n])
    #pragma acc update device(host_array[0:n])

    // Get device pointer
    int *device_ptr = acc_deviceptr(host_array);

    // Verify device pointer
    if(device_ptr == device_array) {
        printf("Device pointer is correct.\n");
    } else {
        printf("Device pointer is incorrect.\n");
    }

    // Free device memory
    #pragma acc exit data delete(device_array[0:n])

    // Free host memory
    free(host_array);

    return 0;
}