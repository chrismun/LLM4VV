#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy d2d,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));
    int *a_copy = (int *)malloc(n * sizeof(int));
    int *b_copy = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 2;
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
        #pragma acc exit data copyout(a_copy[0:n], b_copy[0:n])
    }
    for (int x = 0; x < n; ++x){
        if (abs(a[x] - a_copy[x]) > 2){
            err += a[x];
        }
        if (abs(b[x] - b_copy[x]) > 2){
            err += b[x];
        }
    }

    acc_memcpy_d2d(a, a_copy, n * sizeof(int), acc_get_device_num(a), acc_get_device_num(a_copy));
    #pragma acc exit data copyout(a[0:n]) delete(a_copy[0:n])
    for (int x = 0; x < n; ++x){
        if (abs(a[x] - (1 + a_copy[x])) > PRECISION){
            err += 1;
        }
    }

    acc_memcpy_d2d(b, b_copy, n * sizeof(int), acc_get_device_num(b), acc_get_device_num(b_copy));
    #pragma acc exit data copyout(b[0:n]) delete(b_copy[0:n])
    for (int x = 0; x < n; ++x){
        if (abs(b[x] - (2 + b_copy[x])) > PRECISION){
            err += 1;
        }
    }

    #pragma acc update host(c[0:n])
)
    for (int x = 0; x < n; ++x){
        if (abs(c[x] - (3 + PRECISION)) > PRECISION * 4){
            err += 1;
        }
    };

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