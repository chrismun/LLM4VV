#include "acc_testsuite.h"
#ifndef T1
/*T1:host_data construct if clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    bool condition = rand() % 2; // Generating a random boolean
    int host_data = 10;
    int device_data = 20;

    #pragma acc host_data use_device(device_data) if(condition)
    {
        if(condition){
            if(device_data != 20){
                err = 1; // If condition is true, device_data must be available and equal to 20
            }
        } else {
            if(device_data != 10){
                err = 1; // If condition is false, device_data should retain the initial value of host_data which is 10
            }   
        }
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