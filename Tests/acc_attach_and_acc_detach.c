#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Create a buffer to store the data
    int *data = (int *)malloc(sizeof(int) * 10);
    if (data == NULL) {
        err = 1;
    }

    // Create a buffer to store the attached data
    int *attached_data = (int *)malloc(sizeof(int) * 10);
    if (attached_data == NULL) {
        err = 1;
    }

    // Attach the data to the device
    #pragma acc attach(data, attached_data)

    // Check if the data is attached correctly
    if (data != attached_data) {
        err = 1;
    }

    // Detach the data from the device
    #pragma acc detach(data, attached_data)

    // Check if the data is detached correctly
    if (data == attached_data) {
        err = 1;
    }

    // Free the buffers
    free(data);
    free(attached_data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}