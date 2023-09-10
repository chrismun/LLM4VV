#include "acc_testsuite.h"
#ifndef T1
//T1: acc_memcpy_from_device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(3 * n * sizeof(real_t));
    real_t *devdata;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 1;
    }

    devdata = acc_deviceptr(hostdata);

    #pragma acc enter data copyin(a[0:n], b[0:n]) create(hostdata[0:3*n])
    #pragma acc parallel present(hostdata[0:3*n], devdata[0:3*n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            devdata[x] = a[x];
            devdata[n + x] = b[x];
        }
        #pragma acc loop
        for (int x = 0; x < 3 * n; ++x){
                hostdata[x] = devdata[x];
        }
    }
    for (int x = 0; x < n; ++x){
        if (fabs(hostdata[x] - a[x]) > PRECISION){
            err += 1;
        }
        if (fabs(hostdata[n + x] - b[x]) > PRECISION){
            err += 1;
        }
    }

    #pragma acc enter data copyin(hostdata[0:3*n]) copyout(c[0:n])
    #pragma acc parallel present(c[0:n], hostdata[0:3*n], devdata[0:3*n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] += devdata[x] + devdata[n + x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (1 + a[x] + b[x])) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data copyout(a[0:n], b[0:n], c[0:n]) delete(hostdata[0:3*n])
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