#include "acc_testsuite.h"
#ifndef T1
//T1:variable predetermined data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int vars[10];
    for (int x = 0; x < 10; ++x){
        vars[x] = 0;
    }
    vars[0] = 1;

    #pragma acc parallel loop num_gangs(10) num_workers(1) vector_length(1) private(vars)
    for (int x = 0; x < 10; ++x){
        vars[x] += 1;
    }

    for (int x = 0; x < 10; ++x){
        if (vars[x] != 1){
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