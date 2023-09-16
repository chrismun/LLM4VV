#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {

    // Allocate memory using openacc
    float *x = (float*)acc_malloc(10 * sizeof(float));

    // Check if the allocation was successful
    if (x == NULL) {
        printf("Failed to allocate device memory.\n");
        return -1;
    }

    // Perform operations on the device memory ...

    // Free the memory
    acc_free(x);

    // Check allocation status again to verify if it has been deallocated
    if (x != NULL) {
        printf("Memory wasn't correctly freed.\n");
        return -1;
    }

    printf("Memory successfully freed.\n");
    return 0;
}