#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    // Create a new OpenACC context
    acc_context_t context = acc_create_context();

    // Allocate memory for the data
    int *data = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the data
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Free the data
    acc_free(data);

    // Check that the data has been freed
    if (data != NULL) {
        err = 1;
    }

    // Destroy the OpenACC context
    acc_destroy_context(context);

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

    return failcode;
}