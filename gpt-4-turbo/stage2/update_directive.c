#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test for update directive
// T1: update directive, V: 2.7-3.3
int test_update_directive(){
    int err = 0;
    const int size = 100;
    int a[size], b[size];
    srand(SEED);

    // Initialize arrays on the host
    for(int i = 0; i < size; i++) {
        a[i] = rand() % 1000;
        b[i] = a[i];  // b will be used to verify the updates
    }

    // Allocate and initialize array on the device
    #pragma acc enter data copyin(a[0:size])

    // Modify array on the host
    for(int i = 0; i < size; i++) {
        a[i] += 1;
    }

    // Update device with the modified host array
    #pragma acc update device(a[0:size])

    // Further modify the array on the device
    #pragma acc parallel loop present(a)
    for(int i = 0; i < size; i++) {
        a[i] += 1;
    }

    // Update host with the modified device array
    #pragma acc update self(a[0:size])

    // Exit the data region
    #pragma acc exit data delete(a[0:size])

    // Verify that updates occurred correctly
    for(int i = 0; i < size; i++) {
        if(a[i] != b[i] + 2) {
            err++;
            printf("Mismatch at %d: host value = %d, expected value = %d\n", i, a[i], b[i] + 2);
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_update_directive();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }

    return failcode;
}