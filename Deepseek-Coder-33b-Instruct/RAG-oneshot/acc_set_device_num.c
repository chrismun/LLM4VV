#include <stdio.h>
#include <openacc.h>

int main() {
    int device_num = 0;
    acc_set_device_num(device_num, acc_device_nvidia);

    if (acc_get_device_num(acc_device_nvidia) != device_num) {
        printf("Device number is not set correctly.\n");
        return 1;
    }

    printf("Device number is set correctly.\n");
    return 0;
}