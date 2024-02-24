#include <stdio.h>
#include <openacc.h>

int main() {
    acc_init(acc_device_host);
    printf("Device initialized: %d\n", acc_get_device_type());

    acc_init_device(0, acc_device_host);
    printf("Device number: %d\n", acc_get_device_num(acc_device_host));

    acc_shutdown(acc_device_host);
    printf("Device shutdown: %d\n", acc_get_device_type());

    return 0;
}