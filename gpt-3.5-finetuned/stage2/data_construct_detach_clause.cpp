#include "acc_testsuite.h"
#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() != acc_device_none){
        int *a = (int *)malloc(n * sizeof(int));
        real_t *b = new real_t[2*n];
        for (int x = 0; x < n; ++x){
            a[x] = rand() % 10;
        }
        for (int x = 0; x < 2*n; ++x){
            b[x] = 0;
        }
        #pragma acc enter data copyin(a[0:n]) create(b[0:n]) detach(b[0:n])
        #pragma acc parallel
        {
            #pragma acc loop worker
            for (int x = 0; x < n; ++x){
                b[x+n] = a[x] * a[x];
            }
        }
        #pragma acc exit data copyout(b[0:2*n]) delete(a[0:n])
        for (int x = 0; x < n; ++x){
            if (fabs(b[x] - a[x]) > PRECISION){
                err += 1;
            }
        }
        for (int x = 0; x < n; ++x){
            if (fabs(b[x+n] - a[x] * a[x]) > PRECISION){
                err += 1;
            }
        }
        delete[] b;
        free(a);
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