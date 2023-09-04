#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *dev_array;
    acc_malloc(&dev_array, sizeof(int) * 10);

    // Create a host array
    int *host_array = (int *)malloc(sizeof(int) * 10);

    // Initialize the host array with random values
    for (int i = 0; i < 10; i++) {
        host_array[i] = rand() % 100;
    }

    // Copy the host array to the device array
    acc_memcpy(dev_array, host_array, sizeof(int) * 10);

    // Create an attachment counter
    int *attachment_counter = (int *)malloc(sizeof(int));
    *attachment_counter = 0;

    // Attach the device array to the attachment counter
    acc_attach(dev_array, attachment_counter, sizeof(int));

    // Increment the attachment counter
    *attachment_counter = *attachment_counter + 1;

    // Detach the device array from the attachment counter
    acc_detach(dev_array, attachment_counter);

    // Check if the attachment counter is still attached to the device array
    if (acc_is_attached(dev_array, attachment_counter)) {
        err = 1;
    }

    // Free the device array and host array
    acc_free(dev_array);
    free(host_array);

    return err;
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
    return failcode;
}