#include <iostream>
#include <cstdlib>

int main() {
    int device_type = acc_get_device_type();
    std::cout << "Device type: " << device_type << std::endl;
    return 0;
}