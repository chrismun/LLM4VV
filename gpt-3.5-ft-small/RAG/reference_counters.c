#ifndef T1
//T1:runtime,data,data-region,default-mapping,construct-independent,V:1.0-3.1
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t *c = (real_t *)malloc(3 * n * sizeof(real_t));
    real_t *d = (real_t *)malloc(4 * n * sizeof(real_t));
    real_t *e = (real_t *)malloc(5 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n])
    {
        err = 0;
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                    b[x] += a[x];
            }
        }

        for (int x = 0; x < n; ++x){
            if(fabs(b[x] - a[x]) > PRECISION){
                err += 1;
            }
        }
    }

    acc_init(acc_device_default);

    #pragma acc data copyin(a[0:n]) create(d[0:n][1]) create(c[0:n][2]) create(e[0:n][3])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x];
                d[x] = a[x];
                e[x] = a[x];
            }
        }
    }

    acc_shutdown(acc_device_default);

    #pragma acc data present(a[0:n]) present(c[0:n][2]) present(d[0:n][1]) present(e[0:n][3])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc atomic
                    c[x] += d[x] + e[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
            if (fabs(c[x] - a[x] - a[x]) > PRECISION){
                err += 1;
            }
    }

    for (int x = 0; x < n; ++x){
            if (fabs(d[x] - a[x]) > PRECISION){
                err += 1;
            }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,data-region,devonly,construct-independent,reference-counting,V:1.0-3.1
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(58 * n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
            a[x] = 1;
            b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        err = 0;
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                    b[x] += a[x];
            }
        }

        for (int x = 0; x < n; ++x){
            if(fabs(b[x] - 1) > PRECISION){
                err += 1;
            }
        }
    }

    acc_init(acc_device_default);

    #pragma acc data copyin(a[0:n]) create(c[0:58*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                for (int y = 0; y < 58; ++y){
                    c[x + y * n] = a[x];
                }
            }
        }
    }

    acc_shutdown(acc_device_default);

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < 58; ++y){
            if (fabs(c[x + y * n] - 1) > PRECISION){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,alloc,data,data-region,reference-counting,devonly,V:2.0-3.1
int test3(){
    int err = 0;
    real_t *a, *b;
    real_t *c, *d, *e, *f, *g, *h, *i;

    a = (real_t *)acc_malloc(n * sizeof(real_t));
    b = (real_t *)malloc(n * sizeof(real_t));
    c = (real_t *)acc_malloc(n * sizeof(real_t));
    d = (real_t *)malloc(n * sizeof(real_t));

    if (a == NULL || c == NULL){
        err += 1;
    }

    srand(SEED);
    for (int x = 0; x < n; ++x){
            b[x] = 1;
    }

    #pragma acc data copyin(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                    b[x] += 1;
            }
        }
    }

    #pragma acc parallel
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            #pragma acc atomic
                b[x] += 1;
        }
    }

    acc_init(acc_device_default);

    #pragma acc data copyin(b[0:n]) create(e[0:n]) copyin(a[0:n]) create(c[0:n]) pcopyout(d[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = b[x];
                c[x] = b[x];
                d[x] = b[x];
            }
        }
    }

    acc_shutdown(acc_device_default);

    #pragma acc enter data copyin(a[0:n], c[0:n]) create(e[0:n]) present(b[0:n]) exit data delete(a[0:n]) delete(e[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
        #pragma acc enter data copyin(b[0:n], a[0:n]) create(e[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = b[x];
                    e[x] = b[x];
                }
            }
            #pragma acc update host(a[0:n]) async(1)
            #pragma acc update device(b[0:n]) async(2)
            #pragma acc update device(e[0:n]) async(2)
            #pragma acc update host(a[0:n]) async(1)
            #pragma acc wait(1)
            for (int x = 0; x < n; ++x){
                if (fabs(a[x] - 3) > PRECISION){
                    err += 1;
                }
            }
            #pragma acc wait(2)
            for (int x = 0; x < n; ++x){
                if (fabs(b[x] - 3) > PRECISION){
                    err += 1;
                }
            }
            #pragma acc update host(e[0:n])
            for (int x = 0; x < n; ++x){
                if (fabs(e[x] - 3) > PRECISION){
                    err += 1;
                }
            }
        }
    }

    #pragma acc enter data copyin(a[0:n], c[0:n]) create(e[0:n], g[0:n], i[0:n+39]) create(h[0:n+39])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = b[x];
            }
        }
        #pragma acc enter data copyin(d[0:n]) create(g[0:n]) present(c[0:n]) create(h[0:n+39]) async(2)
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = d[x];
                    g[x] = d[x];
                }
            }
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = n; x < n + 39; ++x){
                    h[x] = d[x];
                }
            }
            #pragma acc update host(c[0:n]) async(1)
            #pragma acc update device(d[0:n]) async(2)
            #pragma acc update device(g[0:n]) async(2)
            #pragma acc update host(c[0:n]) async(1)
            #pragma acc wait(1)
            for (int x = 0; x < n; ++x){
                if (fabs(c[x] - 3) > PRECISION){
                    err += 1;
                }
            }
            #pragma acc wait(2)
            for (int x = 0; x < n; ++x){
                if (fabs(d[x] - 3) > PRECISION){
                    err += 1;
                }
            }
            for (int x = n; x < n + 39; ++x){
                if (fabs(h[x] - 3) > PRECISION){
                    err += 1;
                }
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:runtime,alloc,data,data-region,reference-counting,V:2.0-3.1
int test4(){
    int err = 0;
    real_t *a, *b;
    real_t *c, *d;

    a = (real_t *)acc_malloc(n * sizeof(real_t));
    b = (real_t *)malloc(n * sizeof(real_t));
    c = (real_t *)malloc(n * 3 * sizeof(real_t));
    d = (real_t *)malloc(n * 3 * sizeof(real_t));

    if (a == NULL){
        err += 1;
    }

    srand(SEED);

    for (int x = 0; x < n; ++x){
            b[x] = 1;
    }

    #pragma acc data copyin(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                    b[x] += 1;
            }
        }
    }

    #pragma acc data copyin(b[0:n]) create(c[0:3*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = b[x];
                c[x + n] = b[x];
                c[x + 2 * n] = b[x];
            }
        }
    }

    acc_init(acc_device_default);

    #pragma acc data copyin(b[0:n]) copyout(a[0:n]) create(c[0:n]) copyin(d[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = b[x];
                c[x] = b[x];
                d[x] = b[x];
            }
        }
    }

    acc_shutdown(acc_device_default);

    #pragma acc enter data copyin(a[0:n], c[0:n])
    #pragma acc enter data create(d[0:n])
    #pragma acc parallel
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = 0;
        }
        for (int x = 0; x < 3; ++x){
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                c[y + n * x] += d[y];
            }
        }
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            for (int y = 0; y < 3; ++y){
                a[x] += c[x + y * n];
            }
        }
    }
    #pragma acc exit data copyout(a[0:n], c[0:n])
    #pragma acc exit data delete(d[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] * 5 + c[x] - d[x])) > PRECISION){
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif
#ifndef T4
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test4();
    }
    if (failed != 0){
        failcode = failcode + (1 << 3);
    }
#endif
    return failcode;
}