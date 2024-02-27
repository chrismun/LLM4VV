#include <stdlib.h> // Required for the `rand` function.
#include <stdio.h>  // Required for the `printf` function.
#include <openacc.h> // Required for OpenACC functions.

// Define constants for the test.
#define SEED 12345 
#define NUM_TEST_CALLS 10
#define ARRAY_SIZE 100

#ifndef T1
//T1:parallel construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0; // Error flag, assume no error initially.
    srand(SEED); // Seed the random number generator.

    int a[ARRAY_SIZE]; // Create an array to work on.
    int sum = 0, acc_sum = 0; // Initialize CPU sum and OpenACC-calculated sum.

    // Populate 'a' with random numbers and calculate their sum.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        a[i] = rand() % 100; // Fill the array with numbers in the range 0-99.
        sum += a[i]; // Sum up all the elements for later comparison.
    }
    
    // The OpenACC parallel region
    #pragma acc parallel loop reduction(+:acc_sum)
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        acc_sum += a[i]; // Perform the reduction operation on the array elements.
    }

    // Compare the OpenACC-calculated sum with the CPU-calculated sum.
    if (acc_sum != sum) {
        printf("Error: Expected sum: %d, Got sum: %d\n", sum, acc_sum);
        err = 1; // Set error flag if the sums do not match.
    }

    return err; // Return the error status (0 = success, 1 = failure).
}
#endif

int main(){
    int failcode = 0; // Initialize failure code.
    int failed; // Variable to accumulate failures.

    failed = 0; // Assume no failures initially.
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1(); // Call the test function and accumulate failures.
    }
    
    // If there were any failures, update the failcode.
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    
    // Return the failcode.
    return failcode;
}