#include <iostream>
#include <openacc.h>

int main() {
    int device_num = acc_get_device_num(acc_device_nvidia);
    if (device_num == 0) {
        std::cout << "No NVIDIA device found" << std::endl;
        return 1;
    }

    size_t memory_size = acc_get_property(device_num, acc_device_nvidia, acc_property_memory);
    std::cout << "Memory size: " << memory_size << " bytes" << std::endl;

    size_t free_memory = acc_get_property(device_num, acc_device_nvidia, acc_property_free_memory);
    std::cout << "Free memory: " << free_memory << " bytes" << std::endl;

    int shared_memory_support = acc_get_property(device_num, acc_device_nvidia, acc_property_shared_memory_support);
    std::cout << "Shared memory support: " << (shared_memory_support ? "Yes" : "No") << std::endl;

    const char* device_name = acc_get_property_string(device_num, acc_device_nvidia, acc_property_name);
    std::cout << "Device name: " << device_name << std::endl;

    const char* device_vendor = acc_get_property_string(device_num, acc_device_nvidia, acc_property_vendor);
    std::cout << "Device vendor: " << device_vendor << std::endl;

    const char* device_driver = acc_get_property_string(device_num, acc_device_nvidia, acc_property_driver);
    std::cout << "Device driver: " << device_driver << std::endl;

    return 0;
}