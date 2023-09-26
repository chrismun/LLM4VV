#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a global variable that will be linked to the device
    int *global_var;

    // Allocate memory for the global variable on the device
    global_var = (int *)acc_malloc(sizeof(int));

    // Initialize the global variable on the device
    *global_var = 1;

    // Declare a link clause for the global variable
    acc_declare_link(global_var);

    // Use the global variable in an accelerator routine
    int result = 0;
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        result += *global_var;
    }

    // Check the result
    if (result != 10) {
        err = 1;
    }

    // Free the memory for the global variable on the device
    acc_free(global_var);

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