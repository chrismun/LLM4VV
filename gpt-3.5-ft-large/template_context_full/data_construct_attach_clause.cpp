#include "acc_testsuite.h"
#ifndef T1
#define V 2
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = new real_t[n];
    real_t * b = new real_t[n];

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = 0.0;
    }

    #pragma acc enter data create(a[0:n]) create(b[0:n])
    #pragma acc update device(a[0:n]) device(b[0:n])
    #pragma acc data present(a[0:n], b[0:n])
    {
        for (int x = 0; x < n; ++x){
            a[x] = b[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
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