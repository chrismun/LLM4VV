#include <openacc.h>

int main() {
    int err = 0;

    // Declare a variable in device memory
    int *a;
    acc_declare(a, acc_device_memory);

    // Copy data from host to device
    acc_copyin(a, sizeof(int));

    // Perform some computation on the device
    acc_parallel(a, 1, 1, 1);

    // Copy data back to host
    acc_copyout(a, sizeof(int));

    // Free device memory
    acc_free(a);

    return err;
}