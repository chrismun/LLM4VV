#include <stdio.h>
#include <openacc.h>

int main() {
    int async_arg = acc_async_sync;
    int wait_arg = acc_async_sync;
    int dev_num = acc_get_device_num(acc_device_not_host);

    #pragma acc parallel async(async_arg)
    {
        // Do some work here
    }

    acc_wait_device_async(wait_arg, async_arg, dev_num);

    return 0;
}