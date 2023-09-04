c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    // Initialize two arrays with random values
    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        a[i] = rand();
        b[i] = rand();
    }

    // Copy the contents of a to b using the acc memcpy d2d directive
    #pragma acc enter data copyin(a[0:10])
    #pragma acc enter data copyin(b[0:10])
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        b[i] = a[i];
    }
    #pragma acc exit data delete(a[0:10])
    #pragma acc exit data delete(b[0:10])

    // Check if the contents of a and b are the same
    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory allocated for the arrays
    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    // Print the result
    if (failcode == 0) {
        printf("All tests passed\n");
    } else {
        printf("Some tests failed\n");
    }

    return failcode;
}