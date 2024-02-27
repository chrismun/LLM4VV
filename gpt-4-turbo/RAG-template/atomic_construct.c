#include "acc_testsuite.h"
#ifndef T1
//T1:{atomic},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    long total = 0;
    long x = 0;
    long *captured = (long *)malloc(NUM_TEST_CALLS * sizeof(long));
    if (captured == NULL) {
        fprintf(stderr, "Failed to allocate memory for captured\n");
        exit(1);
    }

    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        #pragma acc loop
        for (int i = 0; i < NUM_TEST_CALLS; ++i) {
            long temp;
            #pragma acc atomic capture
            {
                temp = x;
                x = x + 1;
            }
            captured[i] = temp;
        }
    }

    // Verifying the atomic capture
    for(int i = 0; i < NUM_TEST_CALLS; i++){
        total += captured[i];
    }

    // As the operation is atomic, the total should equal the sum of the first N natural numbers (0 to NUM_TEST_CALLS-1), which equals NUM_TEST_CALLS*(NUM_TEST_CALLS-1)/2
    long expected_total = NUM_TEST_CALLS * (NUM_TEST_CALLS - 1) / 2;
    if (total != expected_total) {
        err = 1; // Error if the atomic capture or increment didn't work as expected
    }
    
    free(captured);

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