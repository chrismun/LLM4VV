#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Check if the directive is executed at runtime
    if (omp_get_num_threads() != 1){
        err = 1;
    }

    // Check if the directive is executed on the correct data
    if (omp_get_thread_num() != 0){
        err = 1;
    }

    // Check if the directive is executed independently of the construct
    if (omp_get_level() != 0){
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