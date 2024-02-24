#include <stdio.h>
#include <openacc.h>

int main() {
    acc_set_device_type(acc_device_nvidia);
    printf("Device type: %d\n", acc_get_device_type());
    return 0;
}