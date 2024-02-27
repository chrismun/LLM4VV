#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Assume SEED, NUM_TEST_CALLS, and any other necessary macros are defined elsewhere

// Global variable marked as device_resident
#pragma acc declare create(n) device_resident
int n = 0;

// Test function
int test_device_resident_variable(){
    int err = 0;

    // Increase n by 1 on the device
    #pragma acc parallel deviceptr(n)
    {
        n += 1;
    }

    // Attempt to validate the change without directly accessing 'n' from the host
    int result = 0;
    #pragma acc parallel deviceptr(n) reduction(+:result)
    {
        result = n; // The expected value is 1 after the first increment
    }

    // 'n' should have been incremented to 1 by the device
    if(result != 1){
        err = 1; // Error if the device-resident variable wasn't correctly manipulated
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    // Test device_resident functionality
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_device_resident_variable();
    }
    if (failed != 0){
        failcode += 1; // Use bit 0 to indicate failure
    }

    return failcode;
}