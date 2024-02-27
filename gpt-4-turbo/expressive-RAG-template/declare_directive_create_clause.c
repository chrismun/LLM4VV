#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Custom defines to simulate the acc_testsuite.h functionality
#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 10;
    int *host_array = (int*)malloc(size * sizeof(int));

    // Initializing data
    for (int i = 0; i < size; i++) {
        host_array[i] = rand();
    }

    // Declare the array on the device and create it
    #pragma acc enter data create(host_array[0:size])

    // Use OpenACC to modify the data on the device
    #pragma acc parallel loop copy(host_array[0:size])
    for (int i = 0; i < size; i++) {
        // Increment each element to verify the modification
        host_array[i] += 1;
    }

    // Copy back the data from the device to the host
    #pragma acc exit data copyout(host_array[0:size])

    // Verification
    for (int i = 0; i < size; i++) {
        if (host_array[i] % 2 == 0) { // Checks if modified by the device (increment should make odd numbers even, and even numbers odd)
            err += 1;
        }
    }

    // Cleanup
    free(host_array);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}