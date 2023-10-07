#include "openacc.h"
#include "acc_testsuite.h"
#ifndef T1
/*T1:acc set device num,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int num_devices = acc_get_num_devices(acc_device_nvidia);
    if (num_devices == 0){
        err = 1;
        return err;
    }

    for (int device_number = 0; device_number < num_devices; ++device_number){
        acc_set_device_num( device_number, acc_device_nvidia);
        if (acc_get_device_num(acc_device_nvidia) != device_number){
            err = 1;
            return err;
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