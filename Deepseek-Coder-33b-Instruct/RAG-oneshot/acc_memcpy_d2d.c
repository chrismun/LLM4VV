#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *a, *b;
    int i;

    // Allocate memory on the host
    a = (int*)malloc(SIZE * sizeof(int));
    b = (int*)malloc(SIZE * sizeof(int));

    // Initialize array a on the host
    for(i = 0; i < SIZE; i++) {
        a[i] = i;
    }

    // Copy array a to device 0
    #pragma acc data copyin(a[0:SIZE]) copy(b[0:SIZE])
    {
        // Copy array a to device 1
        #pragma acc memcpy(b, a, SIZE * sizeof(int)) device(1)
    }

    // Verify the copy
    for(i = 0; i < SIZE; i++) {
        if(a[i] != b[i]) {
            printf("Error: a[%d] = %d, b[%d] = %d\n", i, a[i], i, b[i]);
            return 1;
        }
    }

    printf("Copy successful\n");

    // Free memory
    free(a);
    free(b);

    return 0;
}