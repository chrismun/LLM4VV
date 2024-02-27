#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    unsigned int * a = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * b = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * c = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * d = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * pcpu = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * qcpu = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * pcpures = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int * qcpures = (unsigned int *)malloc(n * sizeof(unsigned int));
    real_t dt, et;

    for (int x = 0; x < n; ++x){
        a[x] = (unsigned int) rand() / (real_t)(RAND_MAX / 10);
        b[x] = (unsigned int) rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        d[x] = 0;
        pcpu[x] = 0;
        qcpu[x] = 0;
        pcpures[x] = 0;
        qcpures[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n], d[0:n])
    {
        #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n], d[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = a[x] + b[x];
                }
            }
            acc_memcpy_device(d, c, n * sizeof(int));
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    d[x] = d[x] * d[x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        pcpu[x] = (a[x] + b[x]) * (a[x] + b[x]);
    }

    for (int x = 0; x < n; ++x){
        if (c[x] != d[x]){
            err += abs(c[x] - d[x]);
        }
    }

    for (int x = 0; x < n; ++x){
        qcpu[x] = (a[x] + b[x]) * (a[x] + b[x]);
    }
    for (int x = 0; x < n; ++x){
        qcpures[x] = (a[x] + b[x]) * (a[x] + b[x]);
    }
    for (int x = 0; x < n; ++x){
        pcpures[x] = (a[x] + b[x]) * (a[x] + b[x];
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