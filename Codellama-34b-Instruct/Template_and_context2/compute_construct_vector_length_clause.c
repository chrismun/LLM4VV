#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct vector_length clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the vector length to 4
    #pragma acc parallel vector_length(4)
    {
        // Do some vector operations
        #pragma acc loop vector
        for (int i = 0; i < 10; i++) {
            // ...
        }
    }

    // Check that the vector length was set correctly
    #pragma acc parallel
    {
        int vector_length = acc_get_vector_length();
        if (vector_length != 4) {
            err = 1;
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