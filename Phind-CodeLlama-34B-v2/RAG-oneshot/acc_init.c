#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int err = 0;
    acc_device_t dev_type = acc_get_device_type();
    int dev_num = acc_get_device_num(dev_type);

    printf("Initial device type: %d\n", dev_type);
    printf("Initial device number: %d\n", dev_num);

    acc_init(acc_device_default);
    dev_type = acc_get_device_type();
    dev_num = acc_get_device_num(dev_type);

    printf("After acc_init, device type: %d\n", dev_type);
    printf("After acc_init, device number: %d\n", dev_num);

    acc_init_device(dev_num, acc_device_default);
    dev_type = acc_get_device_type();
    dev_num = acc_get_device_num(dev_type);

    printf("After acc_init_device, device type: %d\n", dev_type);
    printf("After acc_init_device, device number: %d\n", dev_num);

    return err;
}