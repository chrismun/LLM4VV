#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct self clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc serial self if(1)
    {
        // Serial region with self clause
        int a = 1;
        int b = 2;
        int c = a + b;
        if (c != 3) {
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