#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random number between 1 and 100
    int num = rand() % 100 + 1;

    // Create an array of size num
    int* arr = (int*)malloc(num * sizeof(int));

    // Initialize the array with random values
    for (int i = 0; i < num; i++) {
        arr[i] = rand() % 100;
    }

    // Create a new device and copy the array to it
    int dev = acc_get_device_num();
    acc_set_device_num(dev);
    acc_copyin(arr, num * sizeof(int));

    // Create a new async queue and enqueue a kernel that adds 1 to each element in the array
    acc_queue_t queue = acc_create_queue(dev);
    acc_kernel_t kernel = acc_create_kernel(queue, "add_one", num * sizeof(int));
    acc_enqueue_kernel(queue, kernel, arr, num * sizeof(int));

    // Wait for the kernel to complete
    acc_wait_queue(queue);

    // Check that the array has been updated correctly
    for (int i = 0; i < num; i++) {
        if (arr[i] != i + 1) {
            err = 1;
            break;
        }
    }

    // Clean up
    acc_free(arr);
    acc_delete_queue(queue);
    acc_delete_kernel(kernel);

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