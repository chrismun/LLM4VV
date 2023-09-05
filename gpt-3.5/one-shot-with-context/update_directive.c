#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 10;
    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(n * sizeof(int));

    // Initialize a
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }

    // Copy data from host to device
    #pragma acc enter data copyin(a[0:n])

    // Update data on device
    #pragma acc update device(a[0:n])

    // Copy data from device to host
    #pragma acc update self(b[0:n])

    // Print the result
    for (int i = 0; i < n; i++) {
        printf("a[%d] = %d, b[%d] = %d\n", i, a[i], i, b[i]);
    }

    // Free memory
    #pragma acc exit data delete(a[0:n])
    free(a);
    free(b);

    return 0;