#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main()
{
    int i;
    int *data = (int *)malloc(N * sizeof(int));
    int *copy = (int *)malloc(N * sizeof(int));

    // Initialize data
    for (i = 0; i < N; i++) {
        data[i] = i;
        copy[i] = 0;
    }

    // Copy data to GPU
    acc_copyin(data, N * sizeof(int));

    // Copy data from GPU to CPU
    acc_copyout(copy, N * sizeof(int));

    // Check if data is correctly copied
    for (i = 0; i < N; i++) {
        if (copy[i] != data[i]) {
            printf("Error: Data mismatch at index %d\n", i);
            break;
        }
    }

    // Deallocate memory on GPU
    acc_delete(data, N * sizeof(int));

    // Free memory on CPU
    free(data);
    free(copy);

    return 0;
}