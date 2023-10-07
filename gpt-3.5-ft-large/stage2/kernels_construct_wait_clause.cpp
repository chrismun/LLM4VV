#include "acc_testsuite.h"
#ifndef T1
//T1:kernels, wait,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = new real_t[n];
    real_t *b = new real_t[n];
    real_t temp = 0.0;
    int found = 0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(n * 4);
        b[x] = rand() / (real_t)(n * 4);
    }
    for (int x = 0; x < n; ++x){
        temp = temp + a[x] + b[x];
    }

    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
            #pragma acc loop wait(1)
            for (int x = 0; x < n; ++x){
                c[x] = (c[x] - (a[x] + b[x]))) < PRECISION);
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x]) > 2*PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:kernels, wait, private data, reference counting, asynchronous data,devonly,construct-independent,indipendent,2.0,2.7-3.3
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = new real_t[n];
    real_t * b = new real_t[n];
    real_t * c = new real_t[10 * n];
    int first[10];
    int ms = 1000;
    int dev = acc_get_device_type();

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 2;
    }

    if (dev == acc_device_nvidia){
    int * has_failed = (int *)malloc (10 * sizeof(int));
        for (int x = 0; x < 10; ++x) {
            has_failed[x] = 0;
        }
    #pragma acc data copy(c[0:10*n])
    {
        #pragma acc parallel 
        {
            #pragma acc loop
            for (int x = 0; x < 10 * n; ++x){
                c[x] = 3;
            }
        }
        for (int y = 0; y < 10; ++y){
            first[y] = 1;
        }
        for (int x = 0; x < n; ++x){
            #pragma acc kernels wait
            for (int y = 0; y < 10; ++y){
                if (first[y] == 1){
                    first[y] = 0;
                    continue;
                }
                if (fabs(c[y*n + x] - (a[x] + b[x] + 3))) > PRECISION{
                    err += 1;
                    has_failed[y] = 1;
                }
            }
            #pragma acc update host, device(a[0:n], b[0:n])
            #pragma acc kernels wait
            for (int y = 0; y < 10; ++y){
                c[y * n + x] = a[x] + b[x];
            }
            #pragma acc update host(a[0:n], b[0:n]) if (0)
        }
    }
    for (int x = 0; x < 10; ++x){
        if (has_failed[x] == 1){
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
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}