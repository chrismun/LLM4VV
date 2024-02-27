#include <stdlib.h> // for rand
#include <openacc.h> // for OpenACC API
#include "acc_testsuite.h"

#ifndef T1
//T1:acc init,V:2.7-3.3

int test1(){
    int err = 0;
    srand(SEED);

    // Select a random device type from available options for the purpose
    // of this test, it simply uses acc_device_default as a demonstrative type.
    acc_device_t dev_type = acc_device_default;

    // Initialize the OpenACC runtime for the chosen device type.
    acc_init(dev_type);
	
    // Attempt to query the device type post initialization to verify
    // that the runtime has been initialized correctly.
    acc_device_t current_device_type = acc_get_device_type();

    // If the query fails or returns a different device type, consider it an error.
    // Note: This simplistic check is only for demonstrative purposes.
    if(current_device_type != dev_type) {
        err++;
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