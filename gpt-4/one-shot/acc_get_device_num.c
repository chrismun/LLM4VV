#include <stdio.h>
#include <openacc.h>
#include <stdbool.h>

#define NUM_DEVICE_TYPES 2

int main() {
    int failcode = 0;
    int testType;
    int numDevices[NUM_DEVICE_TYPES];
    acc_device_t deviceTypes[NUM_DEVICE_TYPES] = {acc_device_nvidia, acc_device_host};
    char* deviceTypeNames[NUM_DEVICE_TYPES] = {"acc_device_nvidia", "acc_device_host"};

    // Get number of devices for each type
    for (int i = 0; i < NUM_DEVICE_TYPES; i++) {
        numDevices[i] = acc_get_num_devices(deviceTypes[i]);
    }

    // Test acc_get_device_num for each device type
    for (testType = 0; testType < NUM_DEVICE_TYPES; testType++) {
        for (int i = 0; i < numDevices[testType]; i++) {
            acc_set_device_type(deviceTypes[testType]);
            acc_set_device_num(i, deviceTypes[testType]);

            if (acc_get_device_type() == deviceTypes[testType] && acc_get_device_num(deviceTypes[testType]) == i) {
                printf("PASS %s Device %d\n", deviceTypeNames[testType], i);
            } else {
                printf("FAIL %s Device %d\n", deviceTypeNames[testType], i);
                failcode += 1;
            }
        }
    }

    return failcode;
}