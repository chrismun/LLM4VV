#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct self clause,V:2.7-3.3
int test1(){
    int err = 0;
    int sum = 0;
    int i;

    // Initialize array
    int data[ARRAY_SIZE];
    for(i = 0; i < ARRAY_SIZE; i++)
        data[i] = i;

    // Compute sum using compute construct with self clause
    #pragma acc parallel loop compute self(sum)
    for(i = 0; i < ARRAY_SIZE; i++)
        sum += data[i];

    // Verify the correctness of the computed sum
    int expected_sum = (ARRAY_SIZE * (ARRAY_SIZE - 1)) / 2;
    if(sum != expected_sum)
        err = 1;

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