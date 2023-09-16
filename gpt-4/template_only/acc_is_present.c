#include "acc_testsuite.h"

//T1: OpenACC condition assertion, V:2.7-3.3
int test_acc_present(){
    int is_acc_present = 1;
    int err = 0;
    
    #pragma acc parallel copy(is_acc_present)
    {
       if (acc_on_device(acc_device_not_host)) {
            is_acc_present = 0;
        }
    }

    if(is_acc_present){
        fprintf(stderr, "OpenACC is not properly implemented\n");
        err = 1;
    }
    return err;   
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_present();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}