#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy d2d,V:2.7-3.3
int test1(){
    int err = 0;
    size_t size = n * sizeof(real_t);
    real_t *a = (real_t *)malloc(size);
    real_t *b = (real_t *)malloc(size);
    real_t *a_copy = (real_t *)malloc(size);
    int host = acc_get_device_num(acc_get_device_type());
    for (int x = 0; x < n; x++){
        a[x] = rand() / (real_t)(n + 1);
        b[x] = 0;
        a_copy[x] = a[x];
    }

    #pragma acc enter data copyin(a[0:n]) create(a[0:n])
    #pragma acc data copyout(b[0:n])
    {
        #pragma acc parallel present(a[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; x++){
                a[x] = a[x] * 2;
            }
        }
        acc_memcpy_d2d(a, a_copy, size, acc_get_device_num(acc_get_device_type()),(host == 0) ? 1 : 0);
    }
    #pragma acc exit data copyout(a[0:n]) copyout(a[0:n])

    for (int x = 0; x < n; x++){
        if (fabs(a[x] - a_copy[x]) > PRECISION){
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