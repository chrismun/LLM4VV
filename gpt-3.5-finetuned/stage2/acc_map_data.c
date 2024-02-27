#include "acc_testsuite.h"
#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    data_t *devc = (data_t *)malloc(n * sizeof(data_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 1;
        c[x] = 2;
    }

    #pragma acc data copyin(a[0:n], b[0:n])
    {
        for (int x = 0; x < n; ++x){
            devc[x] = acc_create(c + x, 0);
            acc_map_data(c + x, devc[x], n * sizeof(real_t));
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
        for (int x = 0; x < n; ++x){
            acc_unmap_data(c + x);
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
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