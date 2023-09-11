#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int a[n];
    int b[n];
    int c[n];

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
    }

    #pragma acc parallel num_gangs(n) reduction(+:a,b,c)
    {
        a[i] += b[i];
        b[i] += c[i];
        c[i] += a[i];
    }

    for (int i = 0; i < n; i++) {
        if (a[i] != b[i] || b[i] != c[i] || c[i] != a[i]) {
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