#include <iostream>
#include <cstdlib>

int acc_on_device(acc_device_t dev_type) {
    // Check if the device type is a host device
    if (dev_type == acc_device_host) {
        // If the device type is a host device, check if we are currently executing on the host
        if (acc_get_device_type() == acc_device_host) {
            return 1;
        } else {
            return 0;
        }
    }

    // Check if the device type is not a host device
    if (dev_type != acc_device_host) {
        // If the device type is not a host device, check if we are currently executing on a device
        if (acc_get_device_type() != acc_device_host) {
            return 1;
        } else {
            return 0;
        }
    }

    // If the device type is not defined, return an undefined value
    return -1;
}

int main() {
    // Test the acc_on_device routine with different device types
    std::cout << "Testing acc_on_device with device type acc_device_host: " << acc_on_device(acc_device_host) << std::endl;
    std::cout << "Testing acc_on_device with device type acc_device_not_host: " << acc_on_device(acc_device_not_host) << std::endl;
    std::cout << "Testing acc_on_device with device type acc_device_default: " << acc_on_device(acc_device_default) << std::endl;

    return 0;
}