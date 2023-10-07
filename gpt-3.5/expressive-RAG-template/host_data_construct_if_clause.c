#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Replace the condition with the test you want to perform
    if (rand() % 2 == 0){
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}