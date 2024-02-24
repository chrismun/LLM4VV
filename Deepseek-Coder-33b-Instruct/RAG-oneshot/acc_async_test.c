#include <stdio.h>
#include <openacc.h>

int main() {
    int async_arg;
    int dev_num = acc_get_device_num(acc_device_not_host);

    // Create an asynchronous operation
    #pragma acc parallel async(async_arg)
    {
        // Some computation here
    }

    // Wait for the asynchronous operation to complete
    while (!acc_async_test(async_arg)) {
        // Do something else while waiting
    }

    // Check if the asynchronous operation completed on the current device
    if (acc_async_test_all()) {
        printf("Async operation completed on all devices.\n");
    } else {
        printf("Async operation did not complete on all devices.\n");
    }

    // Check if the asynchronous operation completed on the specified device
    if (acc_async_test_device(async_arg, dev_num)) {
        printf("Async operation completed on device %d.\n", dev_num);
    } else {
        printf("Async operation did not complete on device %d.\n", dev_num);
    }

    return 0;
}