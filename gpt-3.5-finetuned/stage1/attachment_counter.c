#include "acc_testsuite.h"
#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n], d[0:n]) create(c[0:n], e[0:n])
    {
        #pragma acc parallel loop num_gangs(10), vector_length(32)
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
            e[x] = c[x] + d[x];
        }
    }
    int h_counter = acc_get_num_attached() > 3;

    #pragma acc exit data delete(a[0:n], b[0:n], c[0:n]) copyout(e[0:n]) async(1)
    #pragma acc exit data delete(a[0:n], b[0:n], d[0:n]) copyout(c[0:n]) async(2)
    #pragma acc exit data delete(c[0:n], b[0:n], d[0:n]) copyout(a[0:n]) async(3)
    #pragma acc wait
    if (h_counter != (acc_get_num_attached() > 3)){
        err += 1;
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