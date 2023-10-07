#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct num_gangs clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t sum = 0.0;
    int num_gangs = 128;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copy(a[0:n], b[0:n])
    {
        #pragma acc kernels num_gangs(num_gangs)
        {
            for (int x = 0; x < n; ++x){
                b[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        sum += b[x];
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (sum / n)) > PRECISION){
            err = 1;
            break;
        }
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