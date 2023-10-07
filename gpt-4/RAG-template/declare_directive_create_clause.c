#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
 
    int len = 10000;
    float a[len], b[len], c[len];
 
    #pragma acc declare create(a[0:len], b[0:len])
 
    for (int i = 0; i < len; ++i)
        a[i] = rand();

    #pragma acc parallel loop present(a,b,c)
    for(int i = 0; i < len; ++i) {
        b[i] = a[i];
        c[i] = a[i] + b[i];
    }

    // Check if all the computations are done correctly
    for(int i = 0; i < len; ++i) {
        if (fabs(c[i] - 2 * a[i]) > 1e-5){
	            err = 1;
	            break;
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}