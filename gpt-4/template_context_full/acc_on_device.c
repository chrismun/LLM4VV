#include "acc_testsuite.h"
    #ifndef T1
    /*T1:acc on device,V:2.0-2.7*/
    int test1(){
        int err = 0;

        #pragma acc parallel
        {
            if (acc_on_device(acc_device_not_host)){
                /* Checks if code is running on a device */
                if(!acc_on_device(acc_device_host)){
                    /* If the code is running on a device, acc_on_device(acc_device_host) should return false */
                } else {
                    err = 1;
                }
            } else {
                err = 1;
            }
        }

        /* Check if code is running on host */
        if (!acc_on_device(acc_device_not_host)){
            if(acc_on_device(acc_device_host)){
                /* If code is running on the host, acc_on_device(acc_device_host) should return true */
            } else {
                err = 1;
            }
        } else {
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