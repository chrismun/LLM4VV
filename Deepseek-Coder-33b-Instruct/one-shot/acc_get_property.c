#include <stdio.h>
#include <openacc.h>

int main() {
    char name[256];
    acc_device_t device_type = acc_get_device_type();
    acc_get_property(device_type, acc_property_name, 256, name);
    printf("Device name: %s\n", name);
    return 0;
}