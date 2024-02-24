#include <iostream>
#include <cstdlib>
#include <openacc.h>

#define SIZE 100

int main() {
    int *host_data = new int[SIZE];
    int *device_data = new int[SIZE];

    // Initialize host data
    for (int i = 0; i < SIZE; i++) {
        host_data[i] = i;
    }

    // Copy data from host to device
    #pragma acc data copyin(host_data[0:SIZE]) copyout(device_data[0:SIZE])
    {
        #pragma acc memcpy_to_device(device_data, host_data, SIZE * sizeof(int))
    }

    // Check if data was correctly copied
    for (int i = 0; i < SIZE; i++) {
        if (host_data[i] != device_data[i]) {
            std::cout << "Data was not correctly copied from host to device" << std::endl;
            return 1;
        }
    }

    std::cout << "Data was correctly copied from host to device" << std::endl;
    return 0;
}