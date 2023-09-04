c
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Test 1: Check if the compiler supports the executable directive
    if (!acc_is_supported(ACC_EXECUTABLE_DIRECTIVE)){
        err = 1;
    }

    // Test 2: Check if the compiler supports the data directive
    if (!acc_is_supported(ACC_DATA_DIRECTIVE)){
        err = 1;
    }

    // Test 3: Check if the compiler supports the independent clause
    if (!acc_is_supported(ACC_INDEPENDENT_CLAUSE)){
        err = 1;
    }

    // Test 4: Check if the compiler supports the reduction clause
    if (!acc_is_supported(ACC_REDUCTION_CLAUSE)){
        err = 1;
    }

    // Test 5: Check if the compiler supports the private clause
    if (!acc_is_supported(ACC_PRIVATE_CLAUSE)){
        err = 1;
    }

    // Test 6: Check if the compiler supports the firstprivate clause
    if (!acc_is_supported(ACC_FIRSTPRIVATE_CLAUSE)){
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