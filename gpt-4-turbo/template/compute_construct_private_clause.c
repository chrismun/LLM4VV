#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int original_var = rand() / (RAND_MAX / 100); // Generate a random initial value 
    int private_var_copy = original_var; // Copy of the original variable to verify against after parallel execution

    // Implementing the private clause
    #pragma acc parallel private(private_var_copy) // Ensuring private_var_copy is private to each thread
    {
        private_var_copy += 1; // Modifying the variable within the parallel region
    }

    // Check if the original variable remains unchanged after the parallel region
    if (private_var_copy != original_var) {
        err += 1; // If original_var has changed, increment error count
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    // Perform the test NUM_TEST_CALLS times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    // If there are failures, update the failcode
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}