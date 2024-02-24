#include <stdio.h>
#include <openacc.h>

int main() {
    int err = 0;
    int device_num = acc_get_device_num(acc_device_nvidia);
    if (device_num == -1) {
        printf("No NVIDIA device found\n");
        err = 1;
    } else {
        size_t memory_size = acc_get_property(device_num, acc_device_nvidia, acc_property_memory);
        if (memory_size == 0) {
            printf("Failed to get memory size\n");
            err = 1;
        } else {
            printf("Memory size: %zu\n", memory_size);
        }
    }
    return err;
}