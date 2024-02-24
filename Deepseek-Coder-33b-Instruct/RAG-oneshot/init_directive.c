#include <stdio.h>
#include <openacc.h>

int main() {
    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(device_type);

    printf("Initializing device %d of type %d\n", device_num, device_type);

    acc_init(device_type);

    if (acc_get_device_type() == device_type) {
        printf("Device initialized successfully\n");
    } else {
        printf("Device initialization failed\n");
    }

    return 0;
}