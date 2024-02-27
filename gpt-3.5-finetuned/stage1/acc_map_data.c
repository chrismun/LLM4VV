#include "acc_testsuite.h"
#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_host = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = (1 + x) * 0.5;
        b[x] = -(1 + x) * 0.5;
        c[x] = (1 + x) * 0;
        a_host[x] = a[x];
        b_host[x] = b[x];
    }

    #pragma acc enter data create(a[0:n], b[0:n], c[0:n])
    acc_map_data(a, a, n * sizeof(real_t));
    acc_map_data(b, b, n * sizeof(real_t));
    #pragma acc data copyin(c[0:n])
    {
        #pragma acc parallel present(a[0:n], b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }
    acc_unmap_data(a);
    acc_unmap_data(b);
    #pragma acc exit data delete(a[0:n], b[0:n]) copyout(c[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 0) > 3*PRECISION){
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