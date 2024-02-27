#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // complete test here
    #pragma acc parallel loop
    for (int x = 0; x < 1024; ++x){
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *b = (real_t *)malloc(n * sizeof(real_t));
        int c[1];
        c[0] = acc_get_device_num(acc_get_device_type());

        for (int y = 0; y < n; ++y){
            a[y] = rand() / (real_t)(RAND_MAX / 10);
            b[y] = 0;
        }

        #pragma acc data copyin(a[0:n]) copyout(b[0:n])
        {
            #pragma acc wait any
            {
                #pragma acc host_data use_device(c)
                {
                    acc_set_device_num(c[0], acc_get_device_type());
                    #pragma acc loop
                    for (int y = 0; y < n; ++y){
                        b[y] = a[y];
                    }
                }
            }
        }
        for (int y = 0; y < n; ++y){
            if (fabs(b[y] - a[y]) > PRECISION){
                err = 1;
            }
        }

        free(a);
        free(b);
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