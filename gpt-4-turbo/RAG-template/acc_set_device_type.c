#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Setting device type to default. This is just an example.
    // In a real scenario, you might want to try different device types like acc_device_nvidia, acc_device_gpu, etc.
    acc_set_device_type(acc_device_default);

    // Verify if acc_set_device_type set the device type correctly
    acc_device_t current_device_type = acc_get_device_type();
    if(current_device_type != acc_device_default){
        printf("Device type not set correctly. Expected %d, got %d\n", acc_device_default, current_device_type);
        err = 1;
    }

    // Add your OpenACC compute region here to further validate that the device can
    // execute OpenACC code. This is a placeholder illustration. The actual implementation will depend
    // on the device capabilities and what you are trying to test.
    // For example, verifying if a simple data parallel operation can be offloaded and executed.
    int data[100];
    #pragma acc kernels
    for(int i=0; i<100; i++) {
        data[i] = i;
    }

    // Dummy verification to use the data and prevent code removal by an aggressive compiler.
    int sum = 0;
    for(int i=0; i<100; i++) {
        sum += data[i];
    }
    if(sum != 4950) {
        printf("Unexpected computation result, test failed.\n");
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }
    return failcode;
}