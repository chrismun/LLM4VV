#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device queue
    acc_queue_t queue;
    acc_create_queue(&queue);

    // Create a device buffer
    acc_buffer_t buffer;
    acc_create_buffer(&buffer, sizeof(int), acc_device_host);

    // Copy data to the device buffer
    int data = 1;
    acc_copy_to_buffer(buffer, &data, sizeof(int));

    // Wait for the device buffer to be ready
    acc_wait_buffer(buffer);

    // Check that the data has been copied correctly
    int result = 0;
    acc_copy_from_buffer(buffer, &result, sizeof(int));
    if (result != data) {
        err = 1;
    }

    // Clean up
    acc_destroy_buffer(buffer);
    acc_destroy_queue(queue);

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