#include <stdio.h>
#include <openacc.h>

int main() {
    // Initialize OpenACC
    acc_init(acc_device_nvidia);

    // Perform some computations
    // ...

    // Shutdown OpenACC
    acc_shutdown(acc_device_nvidia);

    return 0;
}