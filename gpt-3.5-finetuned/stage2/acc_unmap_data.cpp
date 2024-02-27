#include "acc_testsuite.h"
#ifndef T1
//T1:acc unmap data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = new real_t[n];
    real_t *b = new real_t[n];
    real_t *c = new real_t[n];

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
        c[x] = 0;
    }


    acc_map_data(a, n * sizeof(real_t));
    acc_create(c, n * sizeof(real_t));
    acc_copyin(a,n * sizeof(real_t));
    acc_copyin(b,n * sizeof(real_t));
    acc_copyout(c,n * sizeof(real_t));
    #pragma acc data deviceptr(a,c)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x];
            }
        }
    }
    acc_unmap_data(a);
    acc_copyout(c, n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - a[x]) > PRECISION){
            err = 1;
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