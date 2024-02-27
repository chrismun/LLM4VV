#include "acc_testsuite.h"

#ifndef T1
//T1:acc update device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(3 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    for (int x = 0; x < n; ++x){
        hostdata[x] = a[x];
        hostdata[n + x] = b[x];
        hostdata[2*n + x] = c[x];
    }

    acc_create(hostdata, n * sizeof(real_t))

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
            acc_exe_host_update_self(hostdata, 2 * n * sizeof(real_t));
        }
    }

    acc_update_device(hostdata, 2 * n * sizeof(real_t));

    #pragma acc data copy(c[0:n]) present(a[0:n], b[0:n])
    {
        #pragma parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
                    err += 1;
                }
            }
        }
    }

    free(a);
    free(b);
    free(c);
    free(hostdata);

    return err;
}
#endif
#include "acc_testsuite.h"
#ifndef T1
//T1:acc update device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(3 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    for (int x = 0; x < n; ++x){
        hostdata[x] = a[x];
        hostdata[n + x] = b[x];
        hostdata[2*n + x] = c[x];
    }

    acc_create(hostdata, n * sizeof(real_t));

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
            acc_update_self(c[0:n]);
        }
    }

    #pragma acc exit data copyout(hostdata[0:n]) delete(a[0:n], b[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(hostdata[x] - c[x]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);
    free(hostdata);

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