#include <iostream>
#include <openacc.h>

#ifndef T1
//T1:acc on device,V:2.7-3.3
int test1(){
    int err = 0;
    acc_device_t dev_type = acc_get_device_type();

    if (dev_type == acc_device_not_host) {
        std::cout << "Device is being used." << std::endl;
    } else {
        std::cout << "Device is not being used." << std::endl;
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}