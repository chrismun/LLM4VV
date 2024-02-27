#include "acc_testsuite.h"
#ifndef T1
//T1:serial,V:2.6-3.3
int test1(){
    int err = 0;
    srand(SEED);
    #pragma acc serial num_gangs(16)
    {
        #pragma acc loop gang
        for (unsigned int x = 0; x < 16; ++x){
            if ((size_t) acc_get_num_gangs(acc_get_device_type()) != 16){
                err += 1;
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