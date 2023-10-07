#include <stdio.h>
#include <openacc.h>

void checkGetProperty() {
    size_t deviceMemory;
    const char* deviceName;

    deviceMemory = acc_get_property(0, acc_device_nvidia, acc_property_memory);

    if(deviceMemory == 0)
        printf("Failed to get device memory!\n");
    else
        printf("Device Memory: %zu bytes.\n", deviceMemory);

    deviceName = acc_get_property_string(0, acc_device_nvidia, acc_property_name);

    if(deviceName == NULL)
        printf("Failed to get device name!\n");
    else
        printf("Device Name: %s.\n", deviceName);
}

int main(){
    acc_init(acc_device_nvidia); // change this to your specific device type
    checkGetProperty();
    return 0;
}