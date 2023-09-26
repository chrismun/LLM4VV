#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Create a device pointer
    int *dev_ptr = (int *)acc_malloc(sizeof(int));
    if (dev_ptr == NULL) {
        err = 1;
    }

    // Attach the device pointer to the host pointer
    int *host_ptr = (int *)acc_attach(dev_ptr);
    if (host_ptr == NULL) {
        err = 1;
    }

    // Detach the device pointer from the host pointer
    acc_detach(dev_ptr);

    // Check that the device pointer is no longer attached to the host pointer
    if (acc_is_attached(dev_ptr)) {
        err = 1;
    }

    // Free the device pointer
    acc_free(dev_ptr);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}