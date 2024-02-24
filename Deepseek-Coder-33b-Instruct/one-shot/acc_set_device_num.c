#include <stdio.h>
#include <openacc.h>

int main() {
    int device_num = acc_get_device_num(acc_device_nvidia);
    printf("Current device number: %d\n", device_num);

    acc_set_device_num(0, acc_device_nvidia);
    printf("Device number after setting: %d\n", acc_get_device_num(acc_device_nvidia));

    return 0;
}