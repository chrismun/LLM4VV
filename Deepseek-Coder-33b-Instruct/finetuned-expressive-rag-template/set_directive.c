#include <stdio.h>
#include <openacc.h>

int main() {
    int err = 0;

    #pragma acc set device_type(openacc_device_nvidia)
    {
        if (acc_get_device_type() != acc_device_nvidia) {
            err = 1;
        }
    }

    #pragma acc set device_num(0)
    {
        if (acc_get_device_num(acc_device_nvidia) != 0) {
            err = 1;
        }
    }

    #pragma acc set default_async(1)
    {
        if (acc_get_default_async() != 1) {
            err = 1;
        }
    }

    return err;
}