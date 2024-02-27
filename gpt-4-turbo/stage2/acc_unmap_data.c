#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// In a real testsuite, acc_testsuite.h would provide common functionality and constants.
// #include "acc_testsuite.h" 
#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:acc_unmap_data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1024; // Define the size of the array to be used.
    int *a = (int *)malloc(size * sizeof(int));
    int *host_copy = (int *)malloc(size * sizeof(int)); // Host array to compare

    // Initialize array
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100; // Populate with random values
        host_copy[i] = a[i]; // Copy to host array for verification
    }

    // Map data to the device
    acc_map_data(a, a, size * sizeof(int));

    // Modify the data on the device, if possible. Here it's a dummy modification for demonstration.
    #pragma acc parallel loop present(a[0:size])
    for (int i = 0; i < size; ++i){
        a[i] += 1;
    }

    // Unmap the data. After this call, a should not reflect any changes made on the device.
    acc_unmap_data(a);

    // Verify unmap operation by comparing to the unmodified host copy
    for (int i = 0; i < size; ++i) {
        if (a[i] != host_copy[i]) {
            err++; // If any element differs, unmap did not work as expected.
            break; // No need to check further
        }
    }

    free(a);
    free(host_copy);

    return err; // 0 if successful, nonzero if there was an error.
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
    if(failcode == 0) {
        printf("Test Passed\n");
    } else {
        printf("Test Failed\n");
    }

    return failcode;
}