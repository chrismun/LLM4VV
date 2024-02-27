#include <stdio.h>
#include <openacc.h>

int main() {
    int err = 0;

    // Initialize OpenACC (This function is implicit in most cases but can be used here for clarity)
    acc_init(acc_device_default);

    // Get current device type
    acc_device_t device_type = acc_get_device_type();

    // Optional: Print the device type (for user's understanding)
    switch(device_type) {
        case acc_device_none:
            printf("Current device type: acc_device_none\n");
            break;
        case acc_device_default:
            printf("Current device type: acc_device_default\n");
            break;
        case acc_device_host:
            printf("Current device type: acc_device_host\n");
            break;
        case acc_device_not_host:
            printf("Current device type: acc_device_not_host\n");
            break;
        // As of OpenACC 3.0, these are the fundamental device types. Additional specific device types like GPU, etc., could also be handled.
        default:
            printf("Current device type: Unknown or specific device type\n");
            break;
    }

    // Verify that the device type is valid
    if(device_type != acc_device_none && device_type != acc_device_default &&
       device_type != acc_device_host && device_type != acc_device_not_host) {
        printf("Error: Returned an unknown device type\n");
        err = 1;
    }

    // Shutdown OpenACC (Not strictly necessary but included for completeness)
    acc_shutdown(acc_device_default);
    
    return err;
}