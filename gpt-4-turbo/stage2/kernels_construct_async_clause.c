#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10
#define ARRAY_SIZE 1000

// Utility to initialize array with random data
void initialize_array(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand() % 100; // Random numbers between 0 and 99
    }
}

// Check if the arrays are equal
int check_arrays(int* a, int* b, int size) {
    for (int i = 0; i < size; ++i) {
        if (a[i] != b[i]) {
            return 1; // Arrays are not equal
        }
    }
    return 0; // Arrays are equal
}

// Test the kernels construct with async clause
int test_kernels_construct_async() {
    int err = 0;
    int *a = (int*)malloc(sizeof(int) * ARRAY_SIZE);
    int *b = (int*)malloc(sizeof(int) * ARRAY_SIZE);

    srand(SEED);
    initialize_array(a, ARRAY_SIZE);
    
    // Copy data from host to device and perform operation asynchronously
    #pragma acc kernels copyin(a[0:ARRAY_SIZE]) copyout(b[0:ARRAY_SIZE]) async
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        b[i] = a[i] + 1;
    }

    // Wait for all asynchronous operations to complete
    #pragma acc wait

    // Check results
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (b[i] != a[i] + 1) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_kernels_construct_async();
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}