#include "openacc.h"
#include <stdio.h>

// function to evaluate compiler implementation
void evaluate_compiler_implementation() {
    int num_devices, device_type;

    /* Get number of devices */
    num_devices = acc_get_num_devices(acc_device_nvidia);
    printf("Number of devices: %d\n", num_devices); 

    /* Set device type */
    device_type = acc_set_device_type(acc_device_nvidia);
    printf("Setting device type: successful\n");

    /* Set device number */
    acc_set_device_num(0, acc_device_nvidia);
    printf("Setting device num: successful\n");

    /* Get device type */
    device_type = acc_get_device_type();
    printf("Device type: %d\n", device_type);

    /* Get device number */
    int device_num = acc_get_device_num(acc_device_nvidia);
    printf("Device num: %d\n", device_num); 
}

int main() {
    evaluate_compiler_implementation();
    return 0;
}