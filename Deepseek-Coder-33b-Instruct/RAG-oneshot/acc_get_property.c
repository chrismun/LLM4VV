#include <stdio.h>
#include <openacc.h>

int main() {
    int dev_num = acc_get_device_num(acc_device_default);
    char* dev_name = acc_get_property_string(dev_num, dev_type, acc_property_name);
    char* dev_vendor = acc_get_property_string(dev_num, dev_type, acc_property_vendor);

    if (dev_name == NULL || dev_vendor == NULL) {
        printf("Failed to get device name or vendor.\n");
        return 1;
    }

    printf("Device name: %s\n", dev_name);
    printf("Device vendor: %s\n", dev_vendor);

    return 0;
}