#include <openacc.h>
#include <iostream>

int main() {
    // Initialize the first device of the default device type
    acc_init(acc_device_default);

    // Check that the device was initialized correctly
    if (acc_get_device_type() != acc_device_default) {
        std::cerr << "Error: device was not initialized correctly" << std::endl;
        return 1;
    }

    return 0;
}