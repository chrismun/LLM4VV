#include <openacc.h>
#include <cstdlib>
#include <iostream>

// Assuming these are defined in your acc_testsuite.h or elsewhere
#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:acc get device type,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Setting the device type to default to see if it retrieves correctly
    acc_set_device_type(acc_device_default);

    // Getting the current device type
    auto device_type = acc_get_device_type();

    // Expecting the default device type; this may vary based on the implementation specifics
    if(device_type != acc_device_default) {
        std::cerr << "Unexpected device type. Expected: " << acc_device_default 
                  << ", Got: " << device_type << std::endl;
        err += 1; // Increment error count
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}