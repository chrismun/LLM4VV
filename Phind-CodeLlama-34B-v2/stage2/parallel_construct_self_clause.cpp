#include "acc_testsuite.h"
#ifndef T1
/*T1:parallel construct self clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel self(err)
    {
        int local_err = 0;
        #pragma acc loop
        for (int x = 0; x < 100; ++x) {
            int random = rand() % 2;
            if (random) {
                local_err += 1;
            }
        }
        err += local_err;
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