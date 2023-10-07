#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10
#define TEST_SIZE 1024

int main() {
    int failcode = 0;
    int failed = 0;

    // Allocate memory on the device
    void *d_ptr = acc_malloc(TEST_SIZE);

    // Check if the memory is actually allocated on the device
    if (d_ptr == NULL) {
        printf("Error: acc_malloc failed to allocate memory on the device\n");
        failcode = 1;
    } else {
        // Free the memory on the device
        acc_free(d_ptr);
    }

    // Repeat the test multiple times to ensure consistent behavior
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        d_ptr = acc_malloc(TEST_SIZE);
        if (d_ptr == NULL) {
            failed++;
        } else {
            acc_free(d_ptr);
        }
    }

    if (failed > 0) {
        printf("Error: acc_malloc failed to allocate memory on the device %d times\n", failed);
        failcode = 1;
    }

    return failcode;
}