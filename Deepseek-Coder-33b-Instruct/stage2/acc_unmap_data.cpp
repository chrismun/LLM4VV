#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_ptr;

    // Initialize host array
    for(int i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Map host array to device
    #pragma acc data copyin(host_array[0:N])
    {
        device_ptr = host_array;
    }

    // Unmap host array from device
    acc_unmap_data(host_array);

    // Check if data is still accessible
    for(int i = 0; i < N; i++) {
        if(host_array[i] != i) {
            printf("Data is not accessible after unmap\n");
            return 1;
        }
    }

    printf("Data is accessible after unmap\n");
    return 0;
}