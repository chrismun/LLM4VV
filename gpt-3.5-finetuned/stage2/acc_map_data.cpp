#include "acc_testsuite.h"
#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = new real_t [n];
    real_t *b = new real_t [n];
    real_t *c = new real_t [n];
    
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
        c[x] = 0;
    }

    acc_map_data(&a, a, n * sizeof(real_t));
    #pragma acc data copyin(b[0:n]) deviceptr(a)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * a[x];
            }
        }
    }
    acc_unmap_data(&a);
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
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