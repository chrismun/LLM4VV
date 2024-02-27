#include <stdio.h>
#include <openacc.h>

int main() {
    acc_device_t device_type;
    
    // Initialize OpenACC runtime (might be required on some implementations)
    acc_init(acc_device_none);

    // Attempt to get the current device type
    device_type = acc_get_device_type();

    // Verify the device type returned
    switch (device_type) {
        case acc_device_none:
            printf("Device type has not been selected yet (acc_device_none).\n");
            break;
        case acc_device_default:
            printf("The current device type is the default (acc_device_default).\n");
            break;
        case acc_device_host:
            printf("The current device type is host (acc_device_host).\n");
            break;
        case acc_device_not_host:
            printf("The current device type is not the host (acc_device_not_host).\n");
            break;
        // Add additional cases for other specific device types, like GPUs, as needed.
        default:
            printf("Unknown or unsupported device type.\n");
            break;
    }

    // Finalize OpenACC runtime (might be required on some implementations)
    acc_shutdown(acc_device_none);

    return 0;
}