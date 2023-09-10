#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct attach clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *host_pointer = new int(10);
    int *device_pointer;

    #pragma acc enter data create(device_pointer[0:1])

    #pragma acc parallel present(device_pointer[0:1]) 
    {
        device_pointer = new int[1];
        device_pointer[0] = 20;
    }

    #pragma acc attach (device_pointer)
 
    #pragma acc parallel present(device_pointer[0:1]) 
    {
        host_pointer[0] = device_pointer[0];
    }
    
    // Check if the value changed correctly.
    if (*host_pointer != 20){
        err = 1;
    }

    #pragma acc exit data delete(device_pointer[0:1])
    
    delete []host_pointer;

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