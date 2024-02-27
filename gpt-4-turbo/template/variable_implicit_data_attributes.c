#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Scalar value for testing
    int scalar_val = rand();

    // Copy scalar value to the device and modify it
    #pragma acc parallel private(scalar_val)
    {
        scalar_val += 1;
    }
    // scalar_val should NOT be updated here according to OpenACC's default behavior for scalar variables

    if (scalar_val != rand_val) {
        // If scalar_val was unchanged, test passed, otherwise fail.
        err = 1;
    }

    // Array for aggregate type behavior test
    int array_val[1];
    array_val[0] = rand();

    // Attempt to copy array to the device and modify it
    #pragma acc parallel copy(array_val)
    {
        array_val[0] += 1;
    }
    // array_val[0] SHOULD be updated here, unlike the scalar, as it is explicitly mentioned in the copy clause

    if (array_val[0] == rand_val + 1) {
        // If array_val[0] was correctly updated, part of the test is correct.
    } else {
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