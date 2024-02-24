#include <stdio.h>
#include <openacc.h>

int main() {
    if (acc_get_num_devices(acc_device_nvidia) > 0) {
        printf("OpenACC is supported by the compiler.\n");
    } else {
        printf("OpenACC is not supported by the compiler.\n");
    }

    return 0;
}