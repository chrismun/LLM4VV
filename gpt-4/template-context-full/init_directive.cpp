#include "acc_testsuite.h"
#include <cstdlib>
#include <iostream>

#ifndef T1
/*T1:init directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Test for device_type clause
    try {
        #pragma acc init device_type(acc_device_default) 
    } catch (...) {
        std::cout<< "Device type unsuccessful initialization" << std::endl;
        err = 1; 
    }

    // Test for device_num clause
    try {
        #pragma acc init device_num(0) 
    } catch (...) {
        std::cout<< "Device num unsuccessful initialization" << std::endl;
        err = 1;  
    }

    // Test for if clause
    bool condition = true;
    try {
        #pragma acc init if(condition) 
    } catch (...) {
        std::cout<< "Unsuccessful initialization with if condition" << std::endl;
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