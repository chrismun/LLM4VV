#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 5;
    int *host_array = (int*)malloc(n * sizeof(int));
    int *device_array = (int*)malloc(n * sizeof(int));

    // Initialize host array
    for(int i = 0; i < n; i++) {
        host_array[i] = i;
    }

    // Copy host array to device array
    #pragma acc data copyin(host_array[0:n]) copyout(device_array[0:n])
    {
        #pragma acc kernels
        {
            acc_memcpy_to_device(device_array, host_array, n * sizeof(int));
        }
    }

    // Print device array
    for(int i = 0; i < n; i++) {
        printf("%d ", device_array[i]);
    }

    free(host_array);
    free(device_array);

    return 0;
}