#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a random data array
    int data_size = rand() % 100 + 1;
    int* data = (int*)malloc(data_size * sizeof(int));
    for (int i = 0; i < data_size; i++) {
        data[i] = rand() % 100;
    }

    // Test if the data is present in the current device memory
    int is_present = acc_is_present(data, data_size * sizeof(int));
    if (!is_present) {
        err = 1;
    }

    // Free the data array
    free(data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}