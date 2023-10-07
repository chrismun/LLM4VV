#include <stdio.h>
#include <openacc.h>
 
int main(){
    acc_device_t device_types[] = {acc_device_none, acc_device_default, acc_device_host, acc_device_not_host, acc_device_nvidia};

    char *device_names[] = {"None", "Default", "Host", "Not Host", "NVIDIA"};

    // Initialize the runtime
    acc_init(acc_device_default);

    for(int i = 0; i < sizeof(device_types)/sizeof(acc_device_t); i++){
        int num_devices = acc_get_num_devices(device_types[i]);
        printf("Device Type: %s, Number of Devices: %d\n", device_names[i], num_devices);
    }

    // Finalize the runtime
    acc_shutdown(acc_device_default);
 
    return 0;
}