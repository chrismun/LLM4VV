#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *data = (int*)malloc(N * sizeof(int));
    int i;

    // Initialize data
    for(i = 0; i < N; i++) {
        data[i] = i;
    }

    // Map data to the device
    #pragma acc data copy(data[0:N])
    {
        // Modify data on the device
        #pragma acc kernels
        for(i = 0; i < N; i++) {
            data[i] *= 2;
        }

        // Unmap data
        #pragma acc unmap data
    }

    // Check the results
    for(i = 0; i < N; i++) {
        printf("data[%d] = %d\n", i, data[i]);
    }

    free(data);

    return 0;
}