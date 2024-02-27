#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct default clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(1024 * sizeof(real_t));
    real_t * b = (real_t *)malloc(1024 * sizeof(real_t));
    real_t * a_host = (real_t *)malloc(1024 * sizeof(real_t));
    real_t * b_host = (real_t *)malloc(1024 * sizeof(real_t));

    for (int x = 0; x < 1024; ++x){
        a[x] = (1024 * rand() / (real_t)(RAND_MAX));
        b[x] = 0.0;
        a_host[x] = a[x];
	b_host[x] = 0.0;
    }

    #pragma acc data copyin(a[0:1024]) copyout(b[0:1024])
    {
        #pragma acc kernels default(present)
	{
            #pragma acc loop
            for (int x = 0; x < 1024; ++x){
                b[x] = a[x];
            }
	}
    }

    for (int x = 0; x < 1024; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
        }
    }

    for (int x = 0; x < 1024; ++x){
        if (fabs(a_host[x] - b_host[x]) > PRECISION){
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