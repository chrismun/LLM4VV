#include "acc_testsuite.h"
#ifndef T1
//T1:cache,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);


    real_t m_nocache = 0.0;
    real_t * a = malloc(n * sizeof(real_t));
    real_t * b = malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(n);
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc cache(a[0:1])
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            for (int y = 0; y < n; ++y){
                b[x] += a[(x+y)%n] + m_nocache;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - 4.0 - m_nocache*n) > PRECISION){
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