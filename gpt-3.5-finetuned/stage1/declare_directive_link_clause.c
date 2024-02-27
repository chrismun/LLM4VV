#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive link clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 10; ++x){
        reduce_init(x);
    }

    #pragma acc data copy(a[0:10*n]) present(b[0:n])
    {
        for (int x = 0; x < 10; ++x){
            #pragma acc declare device_link(b(x))
            {
                #pragma acc parallel
                {
                    #pragma acc loop
                    for (int y = 0; y < n; ++y){
                        b[x*n + y] = a[x*n + y];
                    }
                }
            }
            #pragma acc update host(b [x:n])
            for (int y = 0; y < n; ++y){
                if (fabs(b[x * n + y] - a[x * n + y]) > PRECISION){
                    err += 1;
                }
            }
            for (int y = 0; y < x; ++y){
                #pragma acc update host(b[y:n])
                for (int z = 0; z < n; ++z){
                    err += fabs(b[y * n + z]) > PRECISION;
                }
            }
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