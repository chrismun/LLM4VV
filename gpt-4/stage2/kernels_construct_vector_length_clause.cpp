#include "acc_testsuite.h"

#ifndef T1
    /*T1:kernels construct vector_length clause,V:2.0-2.7*/
    int test1(){
        int err = 0;
        srand(SEED);
        int length = 1000;
        float vector1[length];
        float vector2[length];
        float result[length];

        // Initialize vector
        for (int i = 0; i < length; i++) {
            vector1[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            vector2[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        }

        // Compute   result = vector1 * vector2 using the vector_length clause
        #pragma acc kernels vector_length(256)
        for (int i = 0; i < length; i++) {
            result[i] = vector1[i] * vector2[i];
        }

        // Verification
        for (int i = 0; i < length; i++) {
            float expected = vector1[i] * vector2[i];
            if (abs(result[i] - expected) > 1e-5) {
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