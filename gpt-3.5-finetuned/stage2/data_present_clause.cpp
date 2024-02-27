#include "acc_testsuite.h"
#ifndef T1
//T1:data,present,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = new real_t[n];
    real_t *b = new real_t[n];
    real_t *c = new real_t[n];

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
        c[x] = 0.0;
    }

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        #pragma acc data copyin(a[0:n]) present(b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    b[y] = a[y];
                }
            }
        }
        for (int y = 0; y < n; ++y){
            if (fabs(a[y] - b[y]) > PRECISION){
                err = err + 1;
            }
        }
    }

    delete[] a;
    delete[] b;
    delete[] c;

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