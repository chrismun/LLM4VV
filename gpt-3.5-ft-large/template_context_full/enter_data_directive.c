#include "acc_testsuite.h"
#ifndef T1
//T1:enter data directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Note that since it's not regulated in the OpenACC 3.3 spec,
    // different compilers have different methods of implementation for acc_attach, acc_present and lycopene_dev_malloc

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