#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random sequence of integers
    int seq[10];
    for (int i = 0; i < 10; i++) {
        seq[i] = rand() % 100;
    }

    // Use the seq clause to specify the sequence of integers
    #pragma acc parallel loop seq(seq)
    for (int i = 0; i < 10; i++) {
        // Do something with the current element of the sequence
        printf("%d ", seq[i]);
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