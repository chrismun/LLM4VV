#include "acc_testsuite.h"
#ifndef T1
//T1:acc get device num,V:2.7-3.3
int test1(){
    int err = 0;

    for (int x = 0; x < acc_get_num_devices(acc_device_nvidia); ++x){
      acc_set_device_num(x, acc_device_nvidia);
      if (acc_get_device_type() != acc_device_nvidia){
        continue;
      }
    }

    if (acc_get_device_type() != acc_device_none){
        if (acc_get_device_type() == acc_device_host){
            for (int x = 0; x < acc_get_num_devices(acc_device_host); ++x){
                acc_set_device_num(x, acc_device_host);
                if (acc_get_device_type() == acc_device_host){
                    if (acc_get_device_num(acc_device_host) != x){
                        err += 1;
                    }
                }
            }
        }
        else if (acc_get_device_type() == acc_device_not_host){
            for (int x = 0; x < acc_get_num_devices(acc_device_not_host); ++x){
                acc_set_device_num(x, acc_device_not_host);
                if (acc_get_device_type() == acc_device_not_host){
                    if (acc_get_device_num(acc_device_not_host) != x){
                        err += 1;
                    }
                }
            }
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