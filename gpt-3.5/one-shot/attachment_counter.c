#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int num_devices;
    int *device_attachment_counters;

    // Get the number of devices
    #pragma acc control device_type(acc_device_nvidia) \
        device_num(num_devices)
    { }

    // Allocate memory for the attachment counters
    device_attachment_counters = (int *)malloc(num_devices * sizeof(int));
    assert(device_attachment_counters != NULL);

    // Initialize attachment counters to 0
    for (int i = 0; i < num_devices; i++) {
        device_attachment_counters[i] = 0;
    }

    // Attach to each device and increment the attachment counter
    #pragma acc parallel loop
    for (int i = 0; i < num_devices; i++) {
        #pragma acc host_data use_device(device_attachment_counters[i])
        {
            device_attachment_counters[i]++;
        }
    }

    // Print the attachment counters for each device
    for (int i = 0; i < num_devices; i++) {
        printf("Attachment counter for device %d: %d\n", i, device_attachment_counters[i]);
    }

    // Free memory
    free(device_attachment_counters);

    return 0;