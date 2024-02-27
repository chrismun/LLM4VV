#include "acc_testsuite.h"
#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(1 * sizeof(int));
    devtest[0] = 0;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel
    {
	devtest[0] = 1;
    }
    #pragma acc exit data copyout(devtest[0:1])
    if (devtest[0] == 0){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0.0;
        }
        #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n])
        #pragma acc loop attach(c) seq
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
        #pragma acc exit data copyout(a[0:n], b[0:n], c[0:n])
        for (int x = 0; x < n; ++x){
            if (fabs(a[x]) > PRECISION){
                err += 1;
            }
            if (fabs(b[x]) > PRECISION){
                err += 1;
            }
            if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
                err += 1;
            }
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