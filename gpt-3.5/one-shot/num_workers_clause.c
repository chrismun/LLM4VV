#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,data,compute,num_workers,condition,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }
    
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel num_workers(8)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                if(a[x] > 5){
                    b[x] = a[x] * 2;
                }
                else{
                    b[x] = a[x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (a[x] > 5 && fabs(b[x] - (a[x] * 2)) > PRECISION){
            err += 1;
            break;
        }
        if (a[x] <= 5 && fabs(b[x] - a[x]) > PRECISION){
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