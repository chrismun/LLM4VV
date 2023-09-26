#include "acc_testsuite.h"

//T1:acc wait async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device queue
    acc_device_t device = acc_get_device(acc_device_default);
    acc_queue_t queue = acc_create_queue(device, NULL, NULL, 0);

    // Create a data array
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Copy the data to the device
    acc_memcpy_to_device(data, sizeof(data), queue);

    // Create a wait list
    acc_wait_list_t wait_list = acc_create_wait_list(queue);

    // Add the data to the wait list
    acc_wait_list_add(wait_list, data, sizeof(data), 0);

    // Wait for the data to be ready
    acc_wait_async(wait_list, queue);

    // Check if the data is ready
    if (acc_is_ready(data, sizeof(data), queue) == 0) {
        err = 1;
    }

    // Clean up
    acc_destroy_wait_list(wait_list);
    acc_destroy_queue(queue);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}