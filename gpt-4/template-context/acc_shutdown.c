#include "openacc.h"
#include <stdio.h>

int main()
{
    /* Initialize device type as acc_device_not_host */
    acc_device_t device_type = acc_device_not_host;
  
    printf("Testing OpenACC compiler implementation... \n");
  
    /* Call acc_set_device_type with device_type */
    acc_set_device_type(device_type);
    if (acc_get_device_type() != device_type) {
        printf("acc_set_device_type failed!\n");
        return 1;
    }
    int device_num = acc_get_num_devices(device_type);
    for(int i=0; i<device_num; ++i) {
        /* Call acc_set_device_num with device_type and i */
        acc_set_device_num(i, device_type);
        if (acc_get_device_num(device_type) != i) {
            printf("acc_set_device_num failed for device number %d.\n", i);
            return 1;
        }   
        /* Call acc_shutdown with device_type */
        acc_shutdown(device_type);
    }

    printf("All tests passed successfully! \n");
    return 0;
}