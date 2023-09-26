#include "acc_testsuite.h"

//Test: set device type, acc device type host, acc device type nvidia, acc device type radeon. Version: OpenACC 2.7-3.3
int test_set_device_type(){
    int err = 0;
    
    const acc_device_t initial_device = acc_get_device_type();

    //Test for NVIDIA device type.
    acc_set_device_type(acc_device_nvidia);
    if(acc_get_device_type() != acc_device_nvidia){
        err += 1;
    }
    
    //Test for host device type.
    acc_set_device_type(acc_device_host);
    if(acc_get_device_type() != acc_device_host){
        err += 1;
    }
    
    //Test for Radeon device type.
    acc_set_device_type(acc_device_radeon);
    if(acc_get_device_type() != acc_device_radeon){
        err += 1;
    }
    
    //Reset to initial device type
    acc_set_device_type(initial_device);

    return err;
}

int main(){
    const int NUM_TEST_CALLS = 10;
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_set_device_type();
    }
    if(failed != 0){
        failcode = 1;
    }
    
    return failcode;
}