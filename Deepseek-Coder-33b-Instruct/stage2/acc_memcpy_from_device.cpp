#include <iostream>
#include <openacc.h>

#define N 100

int main() {
    int *data_host = new int[N];
    int *data_device = new int[N];

    // Initialize data on host
    for (int i = 0; i < N; i++) {
        data_host[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(data_host[:N]) copyout(data_device[:N])
    {
        #pragma acc kernels
        for (int i = 0; i < N; i++) {
            data_device[i] = data_host[i];
        }
    }

    // Verify data on host
    for (int i = 0; i < N; i++) {
        if (data_host[i] != data_device[i]) {
            std::cout << "Data verification failed at index " << i << std::endl;
            return 1; // Return non-zero to indicate failure
        }
    }

    std::cout << "Data verification passed" << std::endl;
    return 0; // Return zero to indicate success
}