#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array = NULL;

    // Allocate memory on the device
    #pragma acc enter data create(device_array[0:N])

    // Copy data from host to device
    #pragma acc update device(device_array[0:N])

    // Delete data from the device
    #pragma acc exit data delete(device_array[0:N])

    free(host_array);

    return 0;
}