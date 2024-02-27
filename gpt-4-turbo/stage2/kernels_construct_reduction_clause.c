#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#ifndef T1
// T1:kernels construct reduction clause,V:2.7-3.3
int test1() {
    int err = 0;
    const int size = 1024; // Array size for test
    int *data = (int*)malloc(size * sizeof(int));
    int sum = 0; 
    int expected_sum = 0;

    // Initialize data and compute expected sum
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 100; // Simple bounded randomness
        expected_sum += data[i];
    }

    // Performing reduction operation using OpenACC
    #pragma acc kernels reduction(+:sum)
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }

    // Check if the reduction result matches the expected result
    if (sum != expected_sum) {
        printf("Test failed: Expected sum %d, got %d\n", expected_sum, sum);
        err = 1; // Marking test as failed
    } else {
        printf("Test passed: Expected sum %d, got %d\n", expected_sum, sum);
    }

    free(data); // Cleanup
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x) { // Assuming one call is enough for the demo
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}