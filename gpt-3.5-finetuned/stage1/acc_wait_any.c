#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        int *a = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));
        int *c = (int *)malloc(n * sizeof(int));
        int *d = (int *)malloc(n * sizeof(int));

        for (int y = 0; y < n; ++y){
            a[y] = rand() / (real_t)(RAND_MAX / 10);
            b[y] = rand() / (real_t)(RAND_MAX / 10);
            c[y] = 0;
            d[y] = 0;
        }

        #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n], d[0:n])
        {
            #pragma acc parallel async(1)
            {
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    c[y] = a[y] + b[y];
                }
            }
            #pragma acc parallel async(2)
            {
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    d[y] = a[y] - b[y];
                }
            }
            int waits[2] = {1, 2};
            #pragma acc wait any(waits)
        }

        for (int y = 0; y < n; ++y){
            if (fabs(c[y] - (a[y] + b[y])) > PRECISION){
                err += 1;
            }
            if (fabs(d[y] - (a[y] - b[y])) > PRECISION){
                err += 1;
            }
        }

        free(a);
        free(b);
        free(c);
        free(d);
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