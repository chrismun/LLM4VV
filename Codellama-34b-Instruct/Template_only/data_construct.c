#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data construct
    acc_data_construct data;

    // Set the data construct to be executable
    data.executable = 1;

    // Set the data construct to be independent
    data.independent = 1;

    // Set the data construct to be runtime
    data.runtime = 1;

    // Set the data construct to be data
    data.data = 1;

    // Set the data construct to be V:2.0-2.7
    data.version = "2.0-2.7";

    // Create a new data construct
    acc_data_construct new_data = acc_data_construct_create(data);

    // Check if the data construct is valid
    if (!acc_data_construct_is_valid(new_data)) {
        err = 1;
    }

    // Check if the data construct is executable
    if (!acc_data_construct_is_executable(new_data)) {
        err = 1;
    }

    // Check if the data construct is independent
    if (!acc_data_construct_is_independent(new_data)) {
        err = 1;
    }

    // Check if the data construct is runtime
    if (!acc_data_construct_is_runtime(new_data)) {
        err = 1;
    }

    // Check if the data construct is data
    if (!acc_data_construct_is_data(new_data)) {
        err = 1;
    }

    // Check if the data construct is V:2.0-2.7
    if (!acc_data_construct_is_version(new_data, "2.0-2.7")) {
        err = 1;
    }

    // Destroy the data construct
    acc_data_construct_destroy(new_data);

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