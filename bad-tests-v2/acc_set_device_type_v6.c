#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>


int main(int argc, char* argv[]) {
    // Test: Setting 'acc_device_default'
    acc_set_device_type(acc_device_default);

    // Verify the correct device was set
    if(acc_get_device_type() != acc_device_default) {
        printf("Error: acc_device_default not set.\n");
        return 1;
    }

    // Test: setting 'acc_device_host'
    acc_set_device_type(acc_device_host); 

    // Verify the correct device was set
    if (acc_get_device_type() != acc_device_host) {
        printf("Error: acc_device_host not set.\n");
        return 1;
    }

    // Test: setting 'acc_device_not_host'
    acc_set_device_type(acc_device_not_host);

    // Verify the correct device was set
    if (acc_get_device_type() == acc_device_host) {
        printf("Error: acc_device_not_host not set.\n");
        return 1;
    }

    printf("All tests passed successfully.\n");
    return 0;
}