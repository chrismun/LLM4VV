#include <stdlib.h>
#include <openacc.h>

int main() {
    acc_init(acc_device_nvidia);
    // ... perform some computations ...
    acc_shutdown(acc_get_device_type());
    return 0;
}