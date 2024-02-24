#include <stdio.h>
#include <openacc.h>

int main() {
    int device_num = acc_get_device_num(acc_device_nvidia);

    if (device_num == -1) {
        printf("No NVIDIA devices found.\n");
    } else {
        printf("NVIDIA device number: %d\n", device_num);
    }

    return 0;
}