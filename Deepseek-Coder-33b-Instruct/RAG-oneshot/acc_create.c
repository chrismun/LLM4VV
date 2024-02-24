#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 100;
    int *host_ptr = (int*)malloc(n * sizeof(int));
    int *device_ptr;

    // Initialize host_ptr
    for(int i = 0; i < n; i++) {
        host_ptr[i] = i;
    }

    // Create device_ptr
    #pragma acc data copyin(host_ptr[0:n])
    {
        device_ptr = (int*)acc_create(host_ptr, n * sizeof(int));
    }

    // Verify the device_ptr
    int error = 0;
    for(int i = 0; i < n; i++) {
        if(device_ptr[i] != host_ptr[i]) {
            error = 1;
            break;
        }
    }

    if(error) {
        printf("Verification failed\n");
    } else {
        printf("Verification passed\n");
    }

    free(host_ptr);
    acc_free(device_ptr);

    return 0;
}