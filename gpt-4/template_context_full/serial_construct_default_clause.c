#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct default clause,V:2.0-2.7 */
int test1(){
    int err = 0;
    srand(SEED);
    int a = rand();
    int b;

    #pragma acc serial copyin(a) copyout(b) default(present)
    {
        b = a;
    }

    if(a != b){
        err = 1;
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