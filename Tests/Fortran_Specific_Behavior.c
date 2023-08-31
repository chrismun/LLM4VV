#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Check if the compiler supports the "data" clause
    if (!acc_is_present("data")){
        err = 1;
    }

    // Check if the compiler supports the "executable-data" clause
    if (!acc_is_present("executable-data")){
        err = 1;
    }

    // Check if the compiler supports the "construct-independent" clause
    if (!acc_is_present("construct-independent")){
        err = 1;
    }

    // Check if the compiler supports the "V" clause
    if (!acc_is_present("V")){
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