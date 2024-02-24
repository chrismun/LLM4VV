#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int N = 1000;
    int data[N];
    int result = 0;
    int expected = 0;

    // Initialize data and compute expected result
    for(int i = 0; i < N; i++) {
        data[i] = rand() % 100;
        expected += data[i];
    }

    // Compute result using OpenACC
    #pragma acc parallel loop vector_length(4) copy(data) reduction(+:result)
    for(int i = 0; i < N; i++) {
        result += data[i];
    }

    // Check result
    if(result != expected) {
        err++;
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