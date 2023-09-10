#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct auto clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    for (int x = 0; x < NUM_TEST_CALLS; ++x){

    	int cdevice = acc_get_device_type();
    	if(cdevice == acc_device_none){
            int independent = 1;
            #pragma acc update device(independent)
            independent = 0;

            int auto_clause = 1;
            #pragma acc update device(auto_clause)
            independent = 1;
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