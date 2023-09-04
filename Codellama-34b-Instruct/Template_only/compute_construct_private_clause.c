#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int a = rand();
    int b = rand();
    int c = rand();

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; ++i) {
        a = b + c;
        b = a + c;
        c = b + a;
    }

    if (a != b || b != c || c != a) {
        err = 1;
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