#include <stdio.h>
#include <openacc.h>

int main() {
    int device_num = acc_get_device_num(acc_device_host);
    printf("Current device number: %d\n", device_num);

    acc_set_device_num(0, acc_device_nvidia);
    device_num = acc_get_device_num(acc_device_nvidia);
    printf("New device number: %d\n", device_num);

    return 0;
}