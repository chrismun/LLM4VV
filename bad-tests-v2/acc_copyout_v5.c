#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 10

int main() {
    int *data = (int *)malloc(N * sizeof(int));

    // Initialize the data on the device
    #pragma acc kernels copyout(data[0:N])
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Perform a copyout operation
    #pragma acc exit data copyout(data[0:N])

    // Print the copied data
    for (int i = 0; i < N; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(data);

    return 0;
}