#include <stdio.h>
#include <openacc.h>

int main() {
    acc_device_t deviceType = acc_get_device_type();
    
    // Print the device type
    printf("Device Type: %d\n", deviceType);
    
    return 0;
}