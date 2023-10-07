#include "acc_testsuite.h"
#ifndef T1
//T1:acc delete,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real));
    real_t * b = (real_t *)malloc(n * sizeof(real));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 1;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data copyin(b[0:n])
    #pragma acc parallel present(a[0:n], b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = b[x];
        }
    }
    #pragma acc exit data copyout(a[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(a[x]) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:n], b[0:n])

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