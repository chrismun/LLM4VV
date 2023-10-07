#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(3 * n * sizeof(real_t));
    real_t *devdata;

    for (int x = 0; x < n; ++x){
        hostdata[x] = rand() / (real_t)(RAND_MAX / 10);
        hostdata[n + x] = rand() / (real_t)(RAND_MAX / 10);
        hostdata[2*n + x] = 1;
        a[x] = 2;
        b[x] = 1;
        c[x] = 0;
    }

    devdata = acc_copyin(hostdata, 3 * n * sizeof(real_t));

    #pragma acc data copy(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = devdata[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = devdata[x + n];
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                devdata[x + 2*n] = a[x] + b[x];
            }
        }
        acc_memcpy_device(&c[0], &devdata[2*n], n * sizeof(real_t));
        #pragma acc wait
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
    }

    free(hostdata);
    free(a);
    free(b);
    free(c));
    acc_delete(devdata, 3 * n * sizeof(real_t));

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(3 * n * sizeof(real_t));
    real_t *devdata;

    for (int x = 0; x < n; ++x){
        hostdata[x] = rand() / (real_t)(RAND_MAX / 10);
        hostdata[n + x] = rand() / (real_t)(RAND_MAX / 10);
        hostdata[2*n + x] = 1;
        a[x] = 2;
        b[x] = 1;
        c[x] = 0;
    }

    devdata = acc_copyin(0, 3 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        ((real_t *)devdata)[x] = hostdata[x];
        ((real_t *)devdata)[x + n] = hostdata[n + x];
        ((real_t *)devdata)[x + 2 * n] = 0;
    }

    #pragma acc data copy(c[0:n])
    {
        #pragma acc data copyin(devdata[0:3*n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x) {
                    a[x] = ((real_t *)devdata)[x];
                }
                #pragma acc loop
                for (int x = 0; x < n; ++x) {
                    b[x] = ((real_t *)devdata)[x + n];
                }
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                ((real_t *)devdata)[x + 2 * n] = a[x] + b[x];
            }
        }
        acc_memcpy_device(&devdata[2 * n], &c[0], n * sizeof(real_t));
        #pragma acc wait
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION) {
            err += 1;
        }
    }
    for (int x = 0; x < n; ++x) {
        if (fabs(((real_t *)devdata)[x + 2 * n] - (a[x] + b[x])) > PRECISION) {
            err += 1;
        }
    }

    free(hostdata);
    free(a);
    free(b);
    free(c));
    acc_delete(hostdata, 3 * n * sizeof(real_t));

    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test3(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t  *devdata = acc_copyin(hostdata, 2 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        hostdata[x] = rand() / (real_t)(RAND_MAX / 10);
        hostdata[n + x] = -999;
    }
    #pragma acc data copy(b[0:n])
    {
        acc_memcpy_device(&devdata[0], &hostdata[0], n * sizeof(real_t));
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = ((real_t *)devdata)[x];
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - hostdata[x]) > PRECISION) {
            err += 1;
        }
    }

    #pragma acc update host(hostdata[0:n])
    for (int x = 0; x < n; ++x) {
        if (fabs(hostdata[n + x] - hostdata[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);
    free(hostdata);
    acc_delete(devdata, 2 * n * sizeof(real_t));

    return err;
}
#endif

#ifndef T4
//T4:runtime,data,executable-data,construct-independent,compatibility-features,reference-counting,V:2.5-2.7
int test4(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * hasDevice = (int *)malloc(sizeof(int));
    real_t * hostdata = (real_t *)malloc(n * 4 * sizeof(real_t));
    real_t * devdata;

    hasDevice[0] = 1;
    #pragma acc enter data copyin(hasDevice[0:1])
    if (hasDevice[0] == 0){
        return 0;