#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int a = rand();
    int b = rand();
    int c = rand();

    #pragma acc serial private(a, b, c)
    {
        a = a + b;
        b = b + c;
        c = c + a;
    }

    if (a != b || b != c || c != a){
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