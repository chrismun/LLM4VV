#include <stdio.h>
#include <stdlib.h>
#include <openacc.h> // Include OpenACC support

// Prototype for the test function
int test_parallel_sum();

int main(){
    if (test_parallel_sum() != 0){
        printf("Test failed.\n");
        return 1; // Return non-zero for failure
    }

    printf("Test passed.\n");
    return 0; // Return 0 for success
}

int test_parallel_sum() {
    const int N = 100000; // Size of the array
    int *a = (int *)malloc(sizeof(int) * N);
    int sum_parallel = 0, sum_sequential = 0;
    int err = 0;

    // Initialize the array with random values
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // Compute the sum in parallel
    #pragma acc parallel loop reduction(+:sum_parallel)
    for (int i = 0; i < N; i++) {
        sum_parallel += a[i];
    }

    // Compute the sum sequentially for comparison
    for (int i = 0; i < N; i++) {
        sum_sequential += a[i];
    }

    // Check if the parallel and sequential sums match
    if (sum_parallel != sum_sequential) {
        printf("Mismatch: parallel sum = %d, sequential sum = %d\n", sum_parallel, sum_sequential);
        err = 1; // Set error flag if there is a mismatch
    }

    free(a); // Clean up
    return err; // Return error status
}