#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

//Simple test seed for reproducibility
#define SEED 12345
// Number of times to call the test for reliability
#define NUM_TEST_CALLS 10

// Test function to check the delete clause
int test_delete_clause(){
    int err = 0; // Error flag
    const int size = 1024; // Size of the data array
    int *data;
    
    // Allocate memory on the host
    data = (int *)malloc(size * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Failed to allocate host memory.\n");
        return 1; // Return error
    }

    // Initialize data
    for (int i = 0; i < size; ++i) {
        data[i] = i;
    }

    // Enter data into the device and initiate data region
    #pragma acc enter data copyin(data[0:size])

    // Modify data in parallel on the device
    #pragma acc parallel loop present(data[0:size])
    for (int i = 0; i < size; ++i){
        data[i] += 1;
    }

    // Exit data and use the delete clause to remove it from the device's memory
    #pragma acc exit data delete(data[0:size])

    // Attempt a simple operation after deletion to indirectly test behavior (Note: Actual behavior after this point may vary by implementation)
    #pragma acc parallel loop present(data[0:size])
    for (int i = 0; i < size; ++i){
        data[i] += 1; // This operation's behavior is undefined after the delete clause and is just used here for demonstration purposes.
    }
    
    // Free host memory
    free(data);

    return err; // Return 0 if no errors occurred
}

int main(){
    int failcode = 0;
    // Loop the test to increase reliability
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        if (test_delete_clause() != 0){
            failcode = 1;
            break;
        }
    }
    
    if (failcode) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }
    
    return failcode;
}