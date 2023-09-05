#include <stdio.h>
#include <openacc.h>

int main() {
    int dev_num = 0; // device number
    acc_device_t dev_type = acc_device_nvidia; // device type
    acc_device_property_t property = acc_property_memory; // property to query
    
    size_t memory = acc_get_property(dev_num, dev_type, property);
    
    printf("Total device memory: %zu bytes\n", memory);
    
    return 0;