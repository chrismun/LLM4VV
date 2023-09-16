#include "acc_testsuite.h"
#include "openacc.h"
#ifndef T1
//T1:acc shutdown,V:2.7-3.3
int test1(){
    int err = 0;

    /* Launch a kernel to warm up the device */
    #pragma acc parallel
    {
        /* empty body */
    }

    /* Shut down all devices */
    acc_shutdown(acc_device_all);

    /* Test if we can still start a kernel on the device */
    char* message = NULL;
    #pragma acc parallel copy(message[0:1])
    {
        message = "a";
    }

    if(message[0] == 'a'){
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