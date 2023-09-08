#include "acc_testsuite.h"
#ifndef T1
//T1:async,construct-independent,V:2.7-3.0,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict d = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict e = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict f = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict g = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict h = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict i = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = rand() / (real_t)(RAND_MAX / 10);
        f[x] = 0.0;
        g[x] = rand() / (real_t)(RAND_MAX / 10);
        h[x] = 0.0;
        i[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n], c[0:n], d[0:n], e[0:n], f[0:n], g[0:n], h[0:n], i[0:n])
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
        #pragma acc parallel async(2)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                f[x] = d[x] + e[x];
            }
        }
        #pragma acc parallel async(3)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                h[x] = g[x] + c[x] + f[x];
            }
        }
        #pragma acc update wait(3) async(4)
        {
            for (int x = 0; x < n; ++x){
                i[x] = h[x];
            }
        }
        #pragma acc wait(1, 2)
    }
    for (int x = 0; x < n; ++x){
        if (fabs(i[x] - (a[x] + b[x] + d[x] + e[x] + g[x]))) > PRECISION {
            err += 1;
        }
    }
    for (int x = 0; x < n; ++x){
        if (fabs(c[x]) > 2 * PRECISION){
            err += 1;
        }
        if (fabs(f[x]) > 2 * PRECISION){
            err += 1;
        }
        if (fabs(h[x]) > 4 * PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:async,construct-independent,loop,V:2.7-3.0,V:2.5-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict d = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict e = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = 0.0;
    }

    #pragma acc data copyin(b[0:n], c[0:n], d[0:n]) copyout(a[0:n]) 
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = b[x] + c[x];
            }
        }
        #pragma acc parallel loop async(1)
        for (int x = 0; x < n; ++x){
            a[x] += d[x];
        }
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                e[x] = b[x] + c[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (2 * (b[x] + c[x])))) > PRECISION {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:async,construct-independent,V:2.7-3.0
int test3(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
    }

    #pragma acc data copyin(a[0:n]) async(1)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] += a[x];
            }
        }
    }
    #pragma acc wait(1)
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] + b[x]))) > fabs(a[x]) * PRECISION {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:async,data-dependent,V:2.7-3.0
int test4(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *c = (real_t *)malloc(10 * n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n], c[0:10*n])
    {
        for (int x = 0; x < 10; ++x) {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int y = 0; y < n; ++y) {
                    c[x * n + y] = a[x * n + y] + b[x * n + y];
                }
            }
            #pragma acc update host(c[x * n:n]) async(x)
        }
        for (int x = 0; x < 10; ++x) {
            #pragma acc wait(x)
            #pragma acc parallel
            {
                #pragma acc loop
                for (int y = 0; y < n; ++y) {
                    c[x * n + y] += a[x * n + y] + b[x * n + y];
                }
            }
        }
    }

    for (int x = 0; x < 10 * n; ++x) {
        if (fabs(c[x] - 3 * (a[x] + b[x]))) > 2 * PRECISION {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:async,loop,V:2.7-3.0
int test5(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyout(a[0:n]) copyin(b[0:n])
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                a[x] = b[x];
            }
        }
        #pragma acc update b[0:n] async(1)
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                a[x] += b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(a[x] - 2 * b[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T6
//T6:async,data-dependent,construct-reordering,V:3.1-3.1
int test6(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *c = (real_t *)malloc(10 * n * sizeof(real_t)));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 0.0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 1.0;
    }

    #pragma acc data copy(a[0:10*n], b[0:10*n], c[0:10*n])
    {
        for (int x = 0; x < 10; ++x) {
            #pragma acc data copyin(b[0:10*n])
            {
                #pragma acc parallel
                {
                    #pragma acc loop async(x)
                    for (int y = 0; y < n; ++y) {
                        a[x * n + y] = b[x * n + y];

                    }
                }
                #pragma acc parallel
                {
                    #pragma acc loop async(x)
                    for (int y = 0; y < n; ++y) {
                        a[x * n + y] += c[x * n + y];
                    }
                }
            }
        }
        for (int x = 0; x < 10; ++x) {
            #pragma acc wait(x)
            #pragma acc parallel
            {
                #pragma acc loop
                for (int y = 0; y < n; ++y) {
                    c[x * n + y] += 1;
                }
            }
        }
    }
    for (int x = 0; x < 10 * n; ++x) {
        if (fabs(a[x] - (b[x] + c[x]))) > PRECISION {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T7
//T7:async,devonly,V:2.7-3.0
int test7(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    int _devicenum;
    #pragma acc control async(_devicenum)
    _devicenum = acc_get_device_num(acc_get_device_type());

    if (acc_get_device_type() == acc_device_none){
        return 0;
    }

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(b[0:n], a[0:n])
    {
        #pragma acc parallel async(_devicenum)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                a[x] = b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(a[x] - b[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T8
//T8:async,devonly,construct-independent,V:2.7-3.0
int test8(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(25 * n * sizeof(real_t));
    real_t *b = (real_t *)malloc(25 * n * sizeof(real_t));

    int _devicenum;
    #pragma acc control async(_devicenum)
    _devicenum = acc_get_device_num(acc_get_device_type());

    if (acc_get_device_type() == acc_device_none){
        return 0;
    }

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < 25; ++y) {
            a[x * 25 + y] = 0;
            b[x * 25 + y] = (real_t)rand() / (real_t)(RAND_MAX / 10);
        }
    }

    #pragma acc data copyin(b[0:25*n], a[0:25*n])
    {
        #pragma acc parallel async(_devicenum)
        {
            for (int x = 0; x < n; ++x) {
                #pragma acc loop
                for (int y = 0; y < 25; ++y) {
                    a[x * 25 + y] = b[x * 25 + y];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < 25; ++y) {
            if (fabs(a[x * 25 + y] - b[x * 25 + y]) > PRECISION) {
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T9
//T9:async,devonly,loop,V:2.7-3.0
int test9(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * 10 * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * 10 * sizeof(real_t));

    int _devicenum;
    #pragma acc control async(_devicenum)
    _devicenum = acc_get_device_num(acc_get_device_type());

    if (acc_get_device_type() == acc_device_none){
        return 0;