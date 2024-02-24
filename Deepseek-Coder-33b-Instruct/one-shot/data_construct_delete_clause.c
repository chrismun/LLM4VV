#include <stdlib.h>
#include <openacc.h>

int main() {
    int *host_ptr = (int*)malloc(100 * sizeof(int));
    int *device_ptr;

    // Allocate memory on the device
    #pragma acc data create(device_ptr[0:100])
    {
        // Copy data to the device
        device_ptr = (int*)acc_malloc(100 * sizeof(int));
        #pragma acc update device(device_ptr[0:100])

        // Delete data on the device
        #pragma acc delete(device_ptr)
    }

    free(host_ptr);

    return 0;
}