#include<openacc.h>
#include<stdio.h>

// This macros may throw warnings if the OpenACC versions weren't supported by the compiler
#define TESTING_SIMPLE_PRESENCE
#include "acc_testsuite.h"

int main() {
    int count;
    acc_device_t dev_type;

    dev_type = acc_device_none; //To check the number of none device type    
    count = acc_get_num_devices(dev_type);
    printf("Number of ACC device of 'none' type = %d\n",count);
    
    dev_type = acc_device_default; //To check the number of default device type
    count = acc_get_num_devices(dev_type);
    printf("Number of ACC device of 'default' type = %d\n",count);

    dev_type = acc_device_host;
    count = acc_get_num_devices(dev_type);
    printf("Number of ACC device of 'host' type = %d\n",count);

    dev_type = acc_device_not_host;
    count = acc_get_num_devices(dev_type);
    printf("Number of ACC device of 'not_host' type = %d\n",count);

    dev_type = acc_device_nvidia;
    count = acc_get_num_devices(dev_type);
    printf("Number of ACC device of 'nvidia' type = %d\n",count);

    return 0;
}