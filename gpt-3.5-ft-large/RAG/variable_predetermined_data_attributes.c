#include "acc_testsuite.h"
#ifndef T1
//T1:loop,private,V:3.3-3.3 400
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t avg = 0.0;
    real_t * a_host = (real_t *)malloc(10 * n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 1;
        a_host[x] = 1;
    }
    for (int x = 0; x < 10; ++x){
        a[(int)(n * frand())] = 25;
        a_host[(int)(n * frand())] = 25;
    }

    #pragma acc enter data copyin(a[0:10*n])
    for (int x = 0; x < 10; ++x){
        avg = 0.0;
        #pragma acc data copy(avg)
        {
            #pragma acc parallel loop

            for (int y = 0; y < n; ++y){
                avg += a[x * n + y];
            }
            avg = avg / n;
            #pragma acc parallel loop
            for (int y = 0; y < n; ++y){
                a[x * n + y] = a[x * n + y] / avg;
            }
        }
        #pragma acc exit data copyout(a[x * n:n])
        for (int y = 0; y < n; ++y){
            if (fabs(a[x * n + y] - a_host[x * n + y]) > PRECISION){
                err = 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T_2
//T2:code, mirror,V:3.3-3.3
int test2(){
    int x;
    int dev[1];
    int * host = (int *)malloc(1 * sizeof(int));
    dev[0] = 1;
    host[0] = 0;
    #pragma acc enter data copyin(dev[0:1]) create(host[0:1])
    #pragma acc parallel
    {
        dev[0] = 0;
    }
    #pragma acc exit data copyout(dev[0:1])
    if (dev[0] == 1){
        host[0] = 1;
    }
    for (x = 0; x < 1; x++){
        if (host[x] == dev[x]){
            return 1;
        }
    }
    return 0;
}
#endif

#ifndef T_3
//T3:code, mirror, V:3.3-3.3
int test3(){
    int x;
    int host[1];
    int* dev = (int *)malloc(1 * sizeof(int));
    host[0] = 0;
    dev[0] = 1;
    #pragma acc enter data copyin(dev[0:1]) copy(host[0:1])
    for (x = 0; x < 1; x++) {
    host[x] += dev[x];
    }
    #pragma acc exit data delete(dev[0:1]) copyout(dev[0:1])
    for (x = 0; x < 1; x++) {
    dev[x] += host[x];
    }
    if (dev[0] == 1){
        host[0] = 1;
    }
    for (x = 0; x < 1; x++){
        if (host[x] == dev[x]){
            return 1;
        }
    }
    return 0;