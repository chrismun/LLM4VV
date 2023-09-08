#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait,V:2.7-3.3
int test1(){
    int err = 0;

    // create an async queue
    int async_queue = acc_async_queue();

    // create a device
    int dev_num = acc_device_num();

    // create a data array
    int data[10];

    // create a compute region
    #pragma acc parallel num_gangs(1) vector_length(10)
    {
        // create a data array
        int data[10];

        // initialize the data array
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            data[i] = i;
        }

        // wait for the async queue to complete
        acc_wait(async_queue);

        // check the data array
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            if (data[i] != i) {
                err++;
            }
        }
    }

    // destroy the async queue
    acc_async_queue_destroy(async_queue);

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