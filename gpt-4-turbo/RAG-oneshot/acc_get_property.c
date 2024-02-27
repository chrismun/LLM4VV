#include <stdio.h>
#include <openacc.h>

int main() {
    int dev_count;
    acc_device_t dev_type = acc_get_device_type(); // Get the current device type.
    
    // Attempt to set the device type explicitly if it wasn't auto-detected.
    if (dev_type == acc_device_none) {
        acc_set_device_type(acc_device_default);
        dev_type = acc_get_device_type();
    }
    
    // Check the number of devices of the current type.
    dev_count = acc_get_num_devices(dev_type);
    printf("Number of devices of type %d: %d\n", dev_type, dev_count);
    
    // Ensure there is at least one device of the current type to test.
    if (dev_count > 0) {
        // Querying device properties.
        for (int dev_num = 0; dev_num < dev_count; ++dev_num) {
            size_t device_memory = acc_get_property(dev_num, dev_type, acc_property_memory);
            size_t free_memory = acc_get_property(dev_num, dev_type, acc_property_free_memory);
            int shared_memory_support = (int)acc_get_property(dev_num, dev_type, acc_property_shared_memory_support);
            
            const char *device_name = acc_get_property_string(dev_num, dev_type, acc_property_name);
            const char *device_vendor = acc_get_property_string(dev_num, dev_type, acc_property_vendor);
            const char *device_driver = acc_get_property_string(dev_num, dev_type, acc_property_driver);
            
            // Report the collected properties.
            printf("Device #%d:\n", dev_num);
            printf(" - Name: %s\n", device_name ? device_name : "N/A");
            printf(" - Vendor: %s\n", device_vendor ? device_vendor : "N/A");
            printf(" - Driver: %s\n", device_driver ? device_driver : "N/A");
            printf(" - Total Memory: %zu bytes\n", device_memory);
            printf(" - Free Memory: %zu bytes\n", free_memory);
            printf(" - Shared Memory Support: %s\n", shared_memory_support ? "Yes" : "No");
        }
    } else {
        printf("No OpenACC device found of the current type.\n");
    }
    
    return 0;
}