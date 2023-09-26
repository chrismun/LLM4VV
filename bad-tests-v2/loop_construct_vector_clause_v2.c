#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:loop construct vector clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 1024;
    float array[N];
    
    // Initialization of array elements
    for (int i = 0; i < N; i++)
        array[i] = (float) rand() / RAND_MAX;
    
    // Compute the squares of the values, in parallel
    #pragma acc parallel num_gangs(1) vector_length(256)
    {
        #pragma acc loop gang vector
        for (int i = 0; i < N; i++) {
            array[i] = array[i] * array[i];
        }
    }
    
    // Verification
    for (int i = 0; i < N; i++) {
        float val = (float) rand() / RAND_MAX;
        if (fabs(array[i] - val*val) > 1e-5){
            err = 1;
            break;
        }
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