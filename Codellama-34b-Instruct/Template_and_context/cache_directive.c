#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    int arr[10];
    int i;

    // Initialize the array with random values
    for (i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }

    // Cache the array
    #pragma acc cache(arr)

    // Modify the array
    for (i = 0; i < 10; i++) {
        arr[i] += 1;
    }

    // Check that the array has been modified
    for (i = 0; i < 10; i++) {
        if (arr[i] != i + 1) {
            err = 1;
            break;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test1();
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}