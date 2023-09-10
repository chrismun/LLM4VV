#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct num_workersclause,V:2.0-2.7*/
int test1() {
    int err = 0;
    const int num_workers = 4; // You can change this number based on your needs.
    float actual[num_workers];
    srand(SEED);

    #pragma acc parallel num_workers(num_workers)
    {
        #pragma acc loop worker
        for(int i=0; i<num_workers; i++) {
            actual[i] = i;
        }
    }

    for(int i=0; i<num_workers; i++) {
        if(actual[i] != i) {
            err = 1;
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}