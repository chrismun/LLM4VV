#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() != acc_device_none){
        private_var = rand();
        acc_create(host_var, private_var);

        #pragma acc data copyin(host_var[0:1]) present(private_var[0:1])
        {
            #pragma acc serial
            {
                #pragma acc loop
                for (int x = 0; x < 1; ++x){
                    private_var[x] = host_var[x];
                }
            }
        }

        private_var = abs(private_var - host_var[0]);
        if (private_var == 0){
            return err;
        }
        return err;
    }
    else {
      return err;
    }
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