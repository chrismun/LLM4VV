int main() {
    acc_device_t dev_type;
    int failcode = 0;
    
    // Test setting device type to GPU
    dev_type = acc_device_nvidia_gpu;
    acc_set_device_type(dev_type);
    if (acc_get_device_type() != dev_type) {
        printf("Failed to set device type to GPU\n");
        failcode += 1;
    }
    
    // Test setting device type to CPU
    dev_type = acc_device_host;
    acc_set_device_type(dev_type);
    if (acc_get_device_type() != dev_type) {
        printf("Failed to set device type to CPU\n");
        failcode += 2;
    }
    
    return failcode;
}