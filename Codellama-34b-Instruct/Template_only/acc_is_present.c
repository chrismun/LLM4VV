#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Check if the OpenACC runtime is present
    if (!acc_runtime_present()){
        err = 1;
    }

    // Check if the OpenACC data construct is present
    if (!acc_data_present()){
        err = 1;
    }

    // Check if the OpenACC executable-data construct is present
    if (!acc_executable_data_present()){
        err = 1;
    }

    // Check if the OpenACC construct-independent construct is present
    if (!acc_construct_independent_present()){
        err = 1;
    }

    // Check if the OpenACC version is supported
    if (!acc_version_supported(2.0, 2.7)){
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