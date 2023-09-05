#include <stdio.h>
#include <openacc.h>

int main() {
    // Obtain the device type
    acc_device_t deviceType = acc_get_device_type();

    // Obtain the device number of the current thread
    int deviceNum = acc_get_device_num(deviceType);

    if(deviceNum != -1) {
        printf("Current thread is running on device number %d of type %d\n", deviceNum, (int)deviceType);
    } else {
        printf("No valid device found of type %d\n", (int)deviceType);
    }

    return 0;
}