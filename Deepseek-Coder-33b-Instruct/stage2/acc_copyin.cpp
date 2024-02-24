#include <iostream>
#include <openacc.h>

#define N 10

int main() {
    int data[N];
    int *dev_data;

    // Initialize data on the host
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Allocate memory on the device
    dev_data = new int[N];

    // Copy data to the device
    #pragma acc data copyin(data[0:N])
    {
        // Copy data to the device
        #pragma acc update device(data[0:N])

        // Check if the data was correctly copied
        for (int i = 0; i < N; i++) {
            if (data[i] != dev_data[i]) {
                std::cout << "Error: data was not correctly copied to the device" << std::endl;
                return 1;
            }
        }
    }

    // Free device memory
    delete[] dev_data;

    std::cout << "Success: data was correctly copied to the device" << std::endl;
    return 0;
}