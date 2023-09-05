#include <stdio.h>
#include <openacc.h>

int main() {
    int isDevice = acc_on_device(acc_device_nvidia);
  
    if (isDevice) {
        printf("Running on an NVIDIA GPU\n");
    } else {
        printf("Not running on an NVIDIA GPU\n");
    }
  
    return 0;