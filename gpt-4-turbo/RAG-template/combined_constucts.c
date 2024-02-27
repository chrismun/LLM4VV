#include <stdio.h>
#include <stdlib.h>
#define SEED 12345
#define NUM_ELEMENTS 1000
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);
    int a[NUM_ELEMENTS];
    int i;
    int sum = 0, expected_sum = 0;

    // Initialize array with random data
    for (i = 0; i < NUM_ELEMENTS; ++i){
        a[i] = rand() % 100; // Random numbers 0-99
        expected_sum += a[i]; // Calculate expected sum for verification
    }

    // Perform parallel loop with reduction
    #pragma acc parallel loop reduction(+:sum)
    for (i = 0; i < NUM_ELEMENTS; ++i){
        sum += a[i];
    }

    // Verify the result
    if (sum != expected_sum) {
        printf("Error: Expected sum = %d, Obtained sum = %d\n", expected_sum, sum);
        err = 1;
    } else {
        printf("Test Passed: Expected sum matches obtained sum = %d\n", sum);
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
        printf("Test Failed.\n");
    } else {
        printf("All tests passed successfully.\n");
    }

    return failcode;
}