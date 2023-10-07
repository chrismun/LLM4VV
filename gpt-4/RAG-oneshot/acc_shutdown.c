#include <stdio.h>
#include <openacc.h>

int test_shutdown() {
    int err = 0;
    
    // Check number of devices
    int num_devices = acc_get_num_devices(acc_device_default);
    printf("Number of devices: %d\n", num_devices);
    
    // Shutdown each device
    for(int i = 0; i < num_devices; i++) {
        acc_set_device_num(i, acc_device_default);
        acc_shutdown(acc_device_default);
        printf("Shutdown device: %d\n", i);
    }
    
    // Attempt to retrieve the number of devices and expect an error
    // The application behavior here is undefined according to specification
    num_devices = acc_get_num_devices(acc_device_default);
    if (num_devices != 0) {
        printf("Error: Devices still detected after shutdown\n");
        err = 1;
    }

    return err;
}

int test_shutdown_device() {
    int err = 0;

    // Restart device
    acc_init(acc_device_default);
    int num_devices = acc_get_num_devices(acc_device_default);
    printf("Number of devices: %d\n", num_devices);

    // Shutdown each device individually
    for(int i = 0; i < num_devices; i++) {
        acc_shutdown_device(i, acc_device_default);
        printf("Shutdown device: %d\n", i);
    }
    
    // Attempt to retrieve the number of devices and expect an error
    // The application behavior here is undefined according to specification
    num_devices = acc_get_num_devices(acc_device_default);
    if (num_devices != 0) {
        printf("Error: Devices still detected after individual shutdown\n");
        err = 1;
    }

    return err;
}

int main() {
    int err = test_shutdown();
    err |= test_shutdown_device();
    return err;
}