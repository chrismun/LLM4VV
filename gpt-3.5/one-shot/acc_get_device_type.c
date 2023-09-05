#include "acc_testsuite.h"
void test_get_device_type(){
    acc_device_t device_type;
    acc_get_device_type(acc_get_device_num(acc_get_current_device()), &device_type);
    if(device_type == acc_device_not_host){
        printf("Current device is not host\n");
    }
    else{
        printf("Current device is host\n");
    }
}

int main(){
    test_get_device_type();
    return 0;