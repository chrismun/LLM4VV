#include "acc_testsuite.h"
#ifndef T1
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = new real_t[n];
    real_t * b = new real_t[n];
    real_t * c = new real_t[n];
    real_t * d = new real_t[n];
    real_t *hostdata = new real_t[n * 4];
    real_t *devdata;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        d[x] = 1;
    }

    devdata = reinterpret_cast<real_t*>(acc_copyin(hostdata, n * 4 * sizeof(real_t)));
    #pragma acc data deviceptr(devdata)
    {
        #pragma acc data copyin(a[0:n], b[0:n], d[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    devdata[x] = a[x];
                }
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    devdata[n + x] = b[x];
                }
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    devdata[2*n + x] = d[x];
                }
            }
            acc_memcpy_from_device(hostdata, devdata + n, 2*n*sizeof(real_t));
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = devdata[x] + devdata[n + x] + devdata[2*n + x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x] + 1)) > PRECISION){
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