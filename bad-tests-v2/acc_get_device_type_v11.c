#include <openacc.h>

int main() {
    int device_type;
    acc_get_device_type(&device_type);

    if (device_type == ACC_DEVICE_TYPE_CPU) {
        printf("Device type is CPU\n");
    } else if (device_type == ACC_DEVICE_TYPE_GPU) {
        printf("Device type is GPU\n");
    } else if (device_type == ACC_DEVICE_TYPE_ACCELERATOR) {
        printf("Device type is accelerator\n");
    } else {
        printf("Device type is unknown\n");
    }

    return 0;
}