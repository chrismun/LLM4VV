#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main(){
    int device_type;
    acc_get_device_type(&device_type);
    printf("Device type: %d\n", device_type);
    return 0;
}