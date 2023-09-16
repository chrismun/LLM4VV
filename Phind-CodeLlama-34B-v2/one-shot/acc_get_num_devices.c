#include <stdio.h>
#include <openacc.h>

int main(){
    int num_devices;

    num_devices = acc_get_num_devices(acc_device_nvidia);

    if(num_devices == -1){
        printf("No NVIDIA GPUs found. Exiting...\n");
        return 1;
    }
    else{
        printf("Number of NVIDIA GPUs found: %d\n", num_devices);
    }

    return 0;
}