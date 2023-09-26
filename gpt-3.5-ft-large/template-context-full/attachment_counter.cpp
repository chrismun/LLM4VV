#include "acc_testsuite.h"
#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = new real_t[n];
    real_t * b = new real_t[n];
    real_t * c = new real_t[n];
    real_t **dev = (real_t **)malloc(10 * sizeof(real_t));

    for (int x = 0; x < 10; ++x){
        dev[x] = (real_t *)malloc(n * sizeof(real_t));
    }
    int temp = 0;
    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                dev[0][x] = a[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                dev[1][x] = b[x];
            }
        }
        for (int x = 0; x < 10; ++x){
            temp = x;
            #pragma acc data present(dev[x:1][0:n])
            {
                #pragma acc parallel
                {
                    #pragma acc loop
                    for (int y = 0; y < n; ++y){
                        dev[x][y] = dev[0][y] + dev[1][y];
                    }
                }
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = dev[temp][x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > .00001){   //28
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