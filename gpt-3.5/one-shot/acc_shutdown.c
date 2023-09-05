#include <stdio.h>
#include <openacc.h>

int main() {
    int devices = acc_get_num_devices(acc_device_none);

    #pragma acc parallel
    {
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            printf("Hello World from device %d\n", acc_get_device_num());
        }
    }

    acc_shutdown(acc_device_none);

    return 0;