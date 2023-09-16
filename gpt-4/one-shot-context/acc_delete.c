#include "openacc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 1000
#define ACC_DEVICE NVIDIA

int validate_device_memory(int *device_ptr){
    int err_count = 0;
    int array_host[ARRAY_SIZE];
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (device_ptr[i] != array_host[i]) err_count++;
    }

    return err_count;
}

int main(){
    acc_device_t my_device=ACC_DEVICE;
    acc_set_device_type(my_device);
    
    int *device_ptr;
    int array_host[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array_host[i] = i;
    }

    acc_init(my_device);
    
    // Allocate and copy data to device
    device_ptr = (int *)acc_malloc(ARRAY_SIZE*sizeof(int));
    acc_memcpy_to_device(device_ptr, array_host, ARRAY_SIZE*sizeof(int));
    
    if (validate_device_memory(device_ptr) != 0) {
        printf("Data validation failed after memory copy to the device! \n");
        exit(1);
    }
  
    // Delete the memory in the device
    acc_delete(device_ptr, 0);
  
    // Try to access deleted memory - should print error or unexpected value depending on compiler implementation
    if(validate_device_memory(device_ptr) == 0) {
        printf("Error! Still able to access deleted memory. \n");
    } else {
        printf("Test Passed. Deleted memory not accessible. \n");
    }
  
    acc_shutdown(my_device);
    
    return 0;
}