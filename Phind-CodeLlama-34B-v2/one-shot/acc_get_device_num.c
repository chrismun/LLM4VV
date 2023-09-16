#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main(){
    int num_devices = acc_get_num_devices(acc_device_nvidia);
    printf("Number of NVIDIA devices: %d\n", num_devices);

    for(int i = 0; i < num_devices; i++){
        acc_set_device_num(i, acc_device_nvidia);
        int device_num = acc_get_device_num(acc_device_nvidia);
        printf("Device %d is now active\n", device_num);
    }

    return 0;
}