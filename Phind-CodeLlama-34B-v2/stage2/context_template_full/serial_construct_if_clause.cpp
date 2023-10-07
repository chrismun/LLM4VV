#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct if clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc serial if(1)
    {
        // This region should execute on the current device
        int random = rand() % 100;
        if (random > 50) {
            err = 1;
        }
    }

    #pragma acc serial if(0)
    {
        // This region should execute on the local thread
        int random = rand() % 100;
        if (random <= 50) {
            err = 1;
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