#include "acc_testsuite.h"
#ifndef T2
//T2:free,async,async-length,V:2.5-3.0
int test2(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    #pragma acc enter data create(a[0:n])
    #pragma acc enter data copyin(b[0:n])

    #pragma acc parallel async
    {
        #pragma acc loop gang
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
    }

    #pragma acc wait

    #pragma acc exit data copyout(b[0:n]) delete(a[0:n])

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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}