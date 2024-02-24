#include <stdio.h>
#include <openacc.h>

int main() {
    acc_init(acc_device_nvidia);

    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(acc_device_nvidia);

    printf("Device type: %d\n", device_type);
    printf("Device number: %d\n", device_num);

    return 0;
}