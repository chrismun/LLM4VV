#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = (int*)malloc(N * sizeof(int));

    // Initialize host_data
    for (int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_data[:N]) copyout(device_data[:N])
    {
        #pragma acc host_data use_device(host_data)
        {
            for (int i = 0; i < N; i++) {
                device_data[i] = host_data[i];
            }
        }
    }

    // Verify the results
    for (int i = 0; i < N; i++) {
        if (host_data[i] != device_data[i]) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}