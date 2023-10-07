pp
#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,data,data-region,attach,V:3.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    real_t * a = (real_t*)acc_malloc(n * sizeof(real_t));
    real_t * b = (real_t*)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX/10);
        b[x] = 0.0;
    }
    #pragma acc enter data create(b[0:n])
    #pragma acc enter data attach(a)

    #pragma acc parallel loop present(b[0:n], a[0:n])
    for (int x = 0; x < n; ++x) {
        b[x] = a[x];
    }

    #pragma acc exit data copyout(b[0:n]) detach(a)
    
    // Validate result
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    acc_free(a);
    free(b);
    return err;
}

#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    // Repeat tests to increase coverage
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}