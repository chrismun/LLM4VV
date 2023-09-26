#include "acc_testsuite.h"
#ifndef T1
//T1:acc copyout,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int * a  = (int *)malloc(n * sizeof(int));
    int * a_host = (int *)malloc(n * sizeof(int));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * b_host = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
    devtest[0] = 0;
    #pragma acc enter data copyin(a[0:n], b[0:n], devtest[0:1])
    #pragma acc parallel present(a[0:n],b[0:n])
    {
        devtest[0] = 1;
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = 1;
            b[x] = 1.0;
        }
    }
    #pragma acc exit data copyout(a[0:n], b[0:n], devtest[0:1])
    if (devtest[0] == 0){
        for (int x = 0; x < n; ++x){
            a_host[x] = 1;
            b_host[x] = 1.0;
        }
        for (int x = 0; x < n; ++x){
            if (fabs(a_host[x] - a[x]) > PRECISION){
                err += 1;
            }
            if (fabs(b_host[x] - b[x]) > PRECISION){
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
    int dev = 0;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}