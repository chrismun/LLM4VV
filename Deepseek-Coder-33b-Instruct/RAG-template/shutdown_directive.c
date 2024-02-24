#include <stdio.h>
#include <openacc.h>

int main() {
    acc_init(acc_device_nvidia);
    int device_type = acc_get_device_type();
    if (device_type == acc_device_nvidia) {
        printf("OpenACC is supported on the NVIDIA device\n");
    } else {
        printf("OpenACC is not supported on the NVIDIA device\n");
    }
    acc_shutdown(acc_device_nvidia);
    return 0;
}