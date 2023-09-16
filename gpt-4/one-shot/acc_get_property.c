#include <openacc.h>
#include <stdio.h>

int main() {

    int device_type     = acc_get_property(acc_device_default, acc_get_device_num(acc_device_default), acc_property_device_type);
    int compute_capability_major = acc_get_property(acc_device_default, acc_get_device_num(acc_device_default), acc_property_compute_capability_major);
    int compute_capability_minor = acc_get_property(acc_device_default, acc_get_device_num(acc_device_default), acc_property_compute_capability_minor);
    int num_cores       = acc_get_property(acc_device_default, acc_get_device_num(acc_device_default), acc_property_num_cores);
    int num_multiprocessors = acc_get_property(acc_device_default, acc_get_device_num(acc_device_default), acc_property_num_multiprocessors);
    int async = acc_get_property(acc_device_default, acc_get_device_num(acc_device_default), acc_property_async);
    
    printf("Device type: %d\n", device_type);
    printf("Compute Capability: %d.%d\n", compute_capability_major, compute_capability_minor);
    printf("Number of cores: %d\n", num_cores);
    printf("Number of multiprocessors: %d\n", num_multiprocessors);
    printf("Support for async: %d\n", async);
    
    return 0;
}