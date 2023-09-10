#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (cool_region){ 
        update_host(&cool_region, 1);
        for (int x = 0; x < cool_region * n; ++x){
            if (data[x] == 1){
                err = 1;
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