#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 10

int main() {
    int* data = (int*)malloc(N * sizeof(int));

    // Initialize data in host memory
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Transfer data to the device memory
    #pragma acc enter data copyin(data[0:N])

    // Update the device memory from the corresponding local memory
    #pragma acc update device(data[0:N])

    // Print the updated data from the device memory
    printf("Device data:\n");
    #pragma acc data present(data[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    // Transfer data back to the host memory
    #pragma acc update self(data[0:N])

    // Print the data from host memory
    printf("Host data:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // Free the allocated memory
    #pragma acc exit data delete(data[0:N])
    free(data);

    return 0;
}