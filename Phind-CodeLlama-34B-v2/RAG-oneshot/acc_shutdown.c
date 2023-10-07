#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int i;
    int num_devices = acc_get_num_devices(acc_device_default);

    for (i = 0; i < num_devices; i++) {
        acc_set_device_num(i, acc_device_default);
        printf("Shutting down device %d\n", i);
        acc_shutdown(acc_device_default);
    }

    printf("Shutting down all devices\n");
    acc_shutdown(acc_device_default);

    return 0;
}