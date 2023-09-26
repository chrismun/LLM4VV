#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct detach clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data attach(b[0:n])
    #pragma acc data detach(a[0:n])
    {
        #pragma acc parallel present(a[0:n])
        {
            for (int x = 0; x < n; ++x){
                a[x] *= 2;
            }
        }
    }
    #pragma acc exit data delete(a[0:n])
    #pragma acc exit data detach(b[0:n])

    for (int x = 0; x < n; ++x){
        if (a[x] != b[x]){
            err = 1;
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