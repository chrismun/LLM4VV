#include <stdio.h>
#include <openacc.h>

int main() {
    int err = 0;

    // Get the number of devices
    int num_devices = acc_get_num_devices(acc_device_nvidia);
    if (num_devices < 1) {
        printf("No NVIDIA devices found\n");
        return 1;
    }

    // Get the properties of the first device
    size_t memory = acc_get_property(0, acc_device_nvidia, acc_property_memory);
    size_t free_memory = acc_get_property(0, acc_device_nvidia, acc_property_free_memory);
    const char* name = acc_get_property_string(0, acc_device_nvidia, acc_property_name);
    const char* vendor = acc_get_property_string(0, acc_device_nvidia, acc_property_vendor);
    const char* driver = acc_get_property_string(0, acc_device_nvidia, acc_property_driver);

    // Check if the returned values are valid
    if (memory == 0 || free_memory == 0 || name == NULL || vendor == NULL || driver == NULL) {
        printf("Failed to get device properties\n");
        err = 1;
    }

    return err;
}