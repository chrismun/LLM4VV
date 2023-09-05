#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#if _OPENACC >= 202011
int main(){

    int *host_ptr = (int*) malloc(sizeof(int));

    acc_deviceptr_t dev_ptr = acc_deviceptr(host_ptr);

    if (dev_ptr.device_type == acc_device_current){
        printf("Device pointer: %p\n", dev_ptr.ptr);
    }
    else{
        printf("Null pointer\n");
    }

    free(host_ptr);

    return 0;
}
#else
int main(){
    printf("OpenACC version must be 202011 or higher to support acc_deviceptr.\n");
    return 0;