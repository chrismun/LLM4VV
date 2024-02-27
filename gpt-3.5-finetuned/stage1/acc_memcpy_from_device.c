#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy from device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    //!t1:devonly
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *host_ptr = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t *dev_ptr;

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(c[0:n]) create(host_ptr[0:100*n])
    dev_ptr = (real_t *) acc_deviceptr(host_ptr);

    for (int x = 0; x < 100; ++x){
        for (int y = 0; y < n; ++y){
            host_ptr[x * n + y] = c[y];
        }
    }
    #pragma acc exit data copyout(host_ptr[0:100*n]) delete(c[0:n])

    for (int x = 0; x < 100; ++x){
        #pragma acc enter data copyin(host_ptr[x * n: n]) present(a[0:n], b[0:n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                a[y] += host_ptr[x * n + y];
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                host_ptr[x * n + y] = a[y];
            }
        }
        #pragma acc exit data copyout(host_ptr[x * n: n]) delete(c[0:n]) 
        for (int y = 0; y < n; ++y){
            c[y] = 0;
        }
        #pragma acc enter data copyin(c[0:n])
        dev_ptr = (real_t *) acc_deviceptr(host_ptr);
        #pragma acc enter data copyin(host_ptr[x * n: n]) present(a[0:n], b[0:n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                b[y] = host_ptr[x * n + y];
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                c[y] += b[y];
            }
        }
        #pragma acc exit data delete(c[0:n]) copyout(host_ptr[x * n: n])
        if (fabs(c[0] - a[0]) > PRECISION){
            err += 1;
        }
        // Memory was not getting properly freed unless #pragma acc exit is used at least once
        // Otherwise, in a larger construct, OpenACC probably takes care of it for developers.
        #pragma acc exit data delete(c[0:n])
    }
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x])) > 4*PRECISION){
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