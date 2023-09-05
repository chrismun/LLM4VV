#include <stdio.h>
#include <openacc.h>

int main() {
    int num_devices = acc_get_num_devices(acc_device_default);
    printf("Number of devices: %d\n", num_devices);
    
    return 0;
}