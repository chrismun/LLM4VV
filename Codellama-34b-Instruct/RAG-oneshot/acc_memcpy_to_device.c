#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define NUM_ELEMENTS 1000

int main() {
    int failcode = 0;
    int failed;

    // Allocate memory for the data
    int *data_host = (int *)malloc(NUM_ELEMENTS * sizeof(int));
    int *data_dev = (int *)acc_malloc(NUM_ELEMENTS * sizeof(int));

    // Initialize the data on the host
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        data_host[i] = i;
    }

    // Copy the data from the host to the device
    acc_memcpy_to_device(data_dev, data_host, NUM_ELEMENTS * sizeof(int));

    // Check that the data has been correctly copied
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        if (data_dev[i] != data_host[i]) {
            printf("Error: data_dev[%d] = %d, expected %d\n", i, data_dev[i], data_host[i]);
            failcode++;
        }
    }

    // Free the memory
    free(data_host);
    acc_free(data_dev);

    return failcode;
}