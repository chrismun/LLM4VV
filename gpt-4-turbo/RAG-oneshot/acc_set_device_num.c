#include <stdio.h>
#include <openacc.h>
#include <stdlib.h>

// Simple utility function to check for errors.
void check_acc_error(const char* action) {
    if (acc_get_last_error() != acc_no_error) {
        fprintf(stderr, "Error during %s : %d\n", action, acc_get_last_error());
        exit(EXIT_FAILURE);
    }
}

int main() {
    int dev_num = 0; // Example device number, adjust according to your system
    acc_device_t dev_type = acc_device_default; // Example device type

    // Attempt to set the device number
    acc_set_device_num(dev_num, dev_type);
    check_acc_error("acc_set_device_num");

    // Verify the setting was successful
    int current_dev_num = acc_get_device_num(dev_type);
    acc_device_t current_dev_type = acc_get_device_type();

    if (current_dev_num != dev_num) {
        fprintf(stderr, "Device number mismatch. Expected: %d, Got: %d\n", dev_num, current_dev_num);
        return EXIT_FAILURE;
    }
    if (current_dev_type != dev_type) {
        fprintf(stderr, "Device type mismatch. Expected: %d, Got: %d\n", dev_type, current_dev_type);
        return EXIT_FAILURE;
    }

    printf("acc_set_device_num verification successful.\n");
    return EXIT_SUCCESS;
}