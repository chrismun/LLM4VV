#include "openacc.h"
#include <stdio.h>

void test_device_init(int device_num, acc_device_t device_type) {
    int default_device_num = acc_get_device_num(acc_device_default);
    acc_device_t default_device_type = acc_get_device_type();   
    
    #pragma acc init device_type(device_type) device_num(device_num)
    
    int initialized_device_num = acc_get_device_num(device_type);
    int initialized_device_type = acc_get_device_type();
    
    if (initialized_device_num != device_num || initialized_device_type != device_type) {
        printf("Test failed. Expected device: %d of type: %d. Got device: %d of type: %d\n",
               device_num, (int)device_type, initialized_device_num, (int)initialized_device_type);
    } else {
        printf("Test passed. Initialized device: %d of type, %d correctly\n", device_num, (int)device_type);
    }

    acc_set_device_type(default_device_type);
    acc_set_device_num(default_device_num, acc_get_device_type());
} 

int main() {
    test_device_init(0, acc_device_nvidia);
    return 0;
}