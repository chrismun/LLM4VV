#include "acc_testsuite.h"
#ifndef T1
//T1:acc hostptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_dev = (real_t *)acc_create(a, n * sizeof(real_t));
    real_t *b_dev = (real_t *)acc_create(b, n * sizeof(real_t));
    real_t *c_dev = (real_t *)acc_create(c, n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    acc_copyin(a_dev, n * sizeof(real_t));
    acc_copyin(b_dev, n * sizeof(real_t));
    acc_copyin(c_dev, n * sizeof(real_t));

    #pragma acc parallel present(a_dev[0:n], b_dev[0:n], c_dev[0:n])
    {
        int i = acc_threadid();
        c_dev[i] = a_dev[i] + b_dev[i];
    }

    acc_copyout(c_dev, n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
        }
    }

    acc_delete(a_dev, n * sizeof(real_t));
    acc_delete(b_dev, n * sizeof(real_t));
    acc_delete(c_dev, n * sizeof(real_t));
    free(a);
    free(b);
    free(c);

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