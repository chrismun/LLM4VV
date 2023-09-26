#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * tmp = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n], b[0:n], c[0:n]) copy(tmp[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang
            for (int k = 0; k < n; ++k){
                #pragma acc loop worker private(tmp)
                for (int j = 0; j < n; ++j){
                    tmp[j] = b[j] + c[j];
                    #pragma acc loop vector
                    for (int i = 0; i < n; ++i){
                        a[i] += tmp[j];
                    }
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] + c[x])) > PRECISION){
            err = 1;
        }
    }

    free(a);
    free(b);
    free(c);
    free(tmp);

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