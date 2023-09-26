#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() == acc_device_none) {
        real_t false_margin = pow(exp(1), log(.5)/n);
        data a{
            single rand() / (real_t)(RAND_MAX / 10),
            single rand() / (real_t)(RAND_MAX / 10)
        };

        for (int x = 0; x < n; ++x){
            a.a[x] = rand() / (real_t)(RAND_MAX / 10);
            a.b[x] = rand() / (real_t)(RAND_MAX / 10);
        }
        #pragma acc data copy(a.a[0:n], a.b[0:n])
        #pragma acc serial create(a.c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a.c[x] = 0.0;
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a.c[x] += a.a[x];
            }
            #pragma acc loop wait
            for (int x = 0; x < n; ++x){
                a.c[x] += a.b[x];
            }
        }
        for (int x = 0; x < n; ++x){
            if (fabs(a.c[x] - (a.a[x] + a.b[x])) > false_margin * 2){
                err = 1;
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