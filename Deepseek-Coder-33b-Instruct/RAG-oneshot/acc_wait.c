#include <stdio.h>
#include <openacc.h>

int main() {
    int async_arg;
    int dev_num;

    // Create a parallel region
    #pragma acc parallel async(async_arg)
    {
        // Some computation here
    }

    // Wait for the parallel region to complete
    acc_wait(async_arg);

    // Create a parallel region on a specific device
    dev_num = acc_get_device_num(acc_device_nvidia);
    #pragma acc parallel async(async_arg) device_type(acc_device_nvidia)
    {
        // Some computation here
    }

    // Wait for the parallel region to complete on a specific device
    acc_wait_device(async_arg, dev_num);

    // Wait for all parallel regions to complete
    acc_wait_all();

    // Wait for all parallel regions to complete on a specific device
    acc_wait_all_device(dev_num);

    return 0;
}