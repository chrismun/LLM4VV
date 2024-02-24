#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *data = (int*)malloc(N * sizeof(int));
    int *data_device = (int*)malloc(N * sizeof(int));

    // Initialize data on the host
    for(int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Copy data to the device
    #pragma acc enter data copyin(data[:N])

    // Update data on the device
    #pragma acc update device(data[:N])

    // Copy data back to the host
    #pragma acc update self(data[:N])

    // Check if the data was updated correctly
    for(int i = 0; i < N; i++) {
        if(data[i] != i) {
            return 1;
        }
    }

    return 0;
}