#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc enter data copyin(a[0:10]) create(b[0:10]) if(0)
    // there is no default present. Test passes
    #pragma acc exit data copyout(a[0:10]) delete(b[0:10]) if(0)

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