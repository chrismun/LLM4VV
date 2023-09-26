#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    int x = 0;
    
#pragma acc parallel loop
    for (int i = 0; i < 100; i++) {
#pragma acc atomic
        x++;
    }
    
    if (x != 100) {
        err = 1;
    }
    
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
    
#ifndef T1
    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; ++i) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    
    return failcode;
}