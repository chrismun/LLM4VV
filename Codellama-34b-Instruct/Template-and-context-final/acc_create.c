#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory on the device using acc create
    void *dev_ptr = acc_create(NULL, 1024);
    if (dev_ptr == NULL){
        printf("acc create failed\n");
        err = 1;
    }

    // Check if the memory is correctly allocated
    if (acc_is_present(dev_ptr, 1024) != 1){
        printf("acc create did not allocate memory correctly\n");
        err = 1;
    }

    // Free the memory on the device
    acc_free(dev_ptr);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();
        if (failed != 0){
            failcode = failcode + (1 << x);
        }
    }

    // Return the failcode
    return failcode;
}