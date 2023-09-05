#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int deviceNum = acc_get_device_num(acc_device_not_host);

    if (deviceNum == -1) {
        printf("No devices of type acc_device_not_host available or device type not supported\n");
        return 1;
    } else {
        printf("Device number: %d\n", deviceNum);
    }

    return 0;