#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the gang clause
    acc_init_gang(acc_get_num_gangs());

    // Create a loop with the gang clause
    for (int i = 0; i < 10; i++) {
        // Check if the gang clause is working properly
        if (acc_get_gang_id() != i) {
            err = 1;
            break;
        }
    }

    // Clean up the gang clause
    acc_finalize_gang();

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