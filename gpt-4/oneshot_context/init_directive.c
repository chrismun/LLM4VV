#include <stdio.h>
#include <openacc.h>

void init_test_acc_device() {
    int is_init;
    int num_dev;

    num_dev = acc_get_num_devices(acc_device_default);

    if (num_dev <= 0) {
        printf("No OpenACC capable devices found\n");
        return;
    }

    printf("Total OpenACC capable devices found: %d\n", num_dev); 

    // Using init directive
    #pragma acc init device_type(acc_device_default) device_num(0)
    
    /* Use `acc_on_device` API to check if device is initialized
     * It returns nonzero if called on device else zero 
     */
    #pragma acc parallel
    {
        is_init = acc_on_device(acc_device_default); 
    }

    if (is_init) {
        printf("Device is initialized successfully\n");
    } else {
        printf("Device failed to initialize\n");
    }
}

int main(){

    init_test_acc_device();

    return 0;