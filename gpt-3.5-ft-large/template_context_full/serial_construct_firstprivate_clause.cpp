#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int total = 0;
    int known_total = 0;

    for (int x = 0; x < loopcount; ++x){
        total = 0;
        #pragma acc serial firstprivate(total)
        {
            total += x;
        }

        known_total += x;

        if (total != known_total){
            err += 1;
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