#include <stdio.h>
#include <openacc.h>

int main() {
    // Assuming you are testing for a GPU device type. Change this according to your needs.
    acc_device_t dev_type = acc_device_nvidia; // Example device type, change accordingly.
    int device_num;

    // Initialize OpenACC runtime (some implementations might require this)
    acc_init(dev_type);

    // Retrieve the current device number for the specified device type
    device_num = acc_get_device_num(dev_type);
    
    // Check the return value
    if (device_num == -1) {
        printf("No devices of the specified type (%d) are available, or the type is not supported.\n", dev_type);
    } else {
        printf("The current device number for the specified type (%d) is: %d\n", dev_type, device_num);
    }

    // Shut down OpenACC runtime
    acc_shutdown(dev_type);

    return 0;
}