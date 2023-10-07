#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct async clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t sum = 0.0;
    real_t host_sum = 0.0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
        host_sum += a[x];
    }

    #pragma acc data copy(a[0:n], b[0:n])
    {
        #pragma acc serial async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }

        #pragma acc serial async(2)
        {
            #pragma acc loop reduction(+:sum)
            for (int x = 0; x < n; ++x){
                sum += b[x];
            }
        }
    }

    acc_wait(1);
    acc_wait(2);

    if (fabs(sum - host_sum) > PRECISION){
        err = 1;
    }

    free(a);
    free(b);

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