#include <stdio.h>
#include <openacc.h>

int main() {

    int device_count = acc_get_num_devices(acc_device_all);

    if(device_count > 0) {
        printf("Number of devices available: %d\n", device_count);
        printf("Setting device number to 0\n");

        #pragma acc set device_num(0)
        int current_device = acc_get_device_num(acc_device_all);
        if(current_device == 0) {
            printf("Device number is set to %i as expected\nSuccess.\n", current_device);
        }
        else {
            printf("Device number is %i, not as expected\nFail.\n", current_device);
        }
    }
    else {
        printf("No device available\n");
    }

    return 0;
}