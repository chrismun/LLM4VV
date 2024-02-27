#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int scalar_var = rand(); // Simulating variable initialization

    // Running on the host to store original value
    int original_var_value = scalar_var;

    // Compute construct (we use kernels for this example)
    #pragma acc kernels copy(scalar_var)
    {
        scalar_var = scalar_var + 1; // Modifying variable within the compute construct
    }

    // Compute construct with firstprivate implied for scalar variables outside of a kernels construct
    #pragma acc parallel firstprivate(scalar_var)
    {
        scalar_var = scalar_var + 1; // Further modification should not affect the original value outside of this construct
    }

    // Check if the scalar_var was copied back correctly
    if (scalar_var != original_var_value + 1) {
        err += 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0; 
    int failed = 0;

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