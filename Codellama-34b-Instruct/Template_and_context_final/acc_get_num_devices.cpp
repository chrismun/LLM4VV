#include <iostream>
#include <cstdlib>

int acc_get_num_devices(acc_device_t dev_type) {
    int num_devices = 0;

    // Check if the device type is supported
    if (dev_type == ACC_DEVICE_TYPE_CPU || dev_type == ACC_DEVICE_TYPE_GPU) {
        // Get the number of devices of the specified type
        num_devices = acc_get_num_devices_of_type(dev_type);
    }

    return num_devices;
}

int main() {
    int num_devices = acc_get_num_devices(ACC_DEVICE_TYPE_CPU);
    std::cout << "Number of CPU devices: " << num_devices << std::endl;

    num_devices = acc_get_num_devices(ACC_DEVICE_TYPE_GPU);
    std::cout << "Number of GPU devices: " << num_devices << std::endl;

    return 0;
}