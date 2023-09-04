#include <openacc.h>

int main() {
    int failcode = 0;

    // Create a device and a queue
    acc_device_t device = acc_get_device(acc_device_default);
    acc_queue_t queue = acc_get_queue(device);

    // Set the device and queue properties
    acc_set_device_property(device, acc_device_property_queue, queue);

    // Get the device and queue properties
    acc_device_property_t device_property = acc_get_device_property(device);
    acc_queue_property_t queue_property = acc_get_queue_property(queue);

    // Check that the device and queue properties match the expected values
    if (device_property != acc_device_property_queue || queue_property != acc_queue_property_default) {
        failcode = 1;
    }

    return failcode;
}