#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a = (real_t *)acc_malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        c[x] = 1;
    }

    #pragma acc enter data copyin(a[0:n])

    for (int x = 0; x < n; ++x){
        dev_a[x] = 0;
    }
    #pragma acc update device(dev_a[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(dev_a[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    #pragma acc data copyout(a[0:n])
    {
        #pragma acc parallel present(dev_a[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                dev_a[x] = 1;
            }
        }
        #pragma acc update self(a[0:n])
    }
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - c[x]) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,V:2.5-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a = (real_t *)acc_malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
    }

    #pragma acc enter data copyin(a[0:n])

    #pragma acc data copyout(a[0:n])
    {
        #pragma acc parallel present(dev_a[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                dev_a[x] = 1;
            }
        }
        #pragma acc update self(a[0:n])
    }
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - 2) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,construct-independent,V:2.5-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a = (real_t *)acc_malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
    }

    #pragma acc enter data create(a[0:n])

    #pragma acc data copyout(a[0:n])
    {
        #pragma acc parallel present(dev_a[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                dev_a[x] = 1;
            }
        }
        #pragma acc update if(n % 2 != 0) self(a[1:(n-1):2])
    }
    if (n % 2 == 0){
        for (int x = 1; x < n; x += 2){
            if (fabs(a[x] - 1) > PRECISION){
                err += 1;
            }
        }
    }
    else{
        for (int x = 1; x < n; x += 2){
            if (fabs(a[x] - 2) > PRECISION){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:runtime,data,executable-data,construct-independent,V:2.5-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a = (real_t *)acc_malloc(2 * n * sizeof(real_t));

    for (int x = 0; x < 2 * n; ++x){
        a[x] = 1;
        c[x] = 1;
        dev_a[x] = 0;
    }

    #pragma acc enter data copyin(a[0:2*n])

    #pragma acc data present(dev_a[0:2*n])
    {
        for (int x = 0; x < 2 * n; ++x){
            dev_a[x] += 1;
        }
        #pragma acc update self(a[0:n]) if(n % 2 == 0) else update device(a[n:2*n])
        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - 2) > PRECISION){
                err += 1;
            }
        }
        for (int x = 0; x < n; ++x){
            if (fabs(a[x + n] - 1) > PRECISION){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:runtime,data,executable-data,construct-independent,V:2.5-2.7
int test5(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a = (real_t *)acc_malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        dev_a[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n])

    #pragma acc data present(dev_a[0:n])
    {
        for (int x = 0; x < n; ++x){
            dev_a[x] += 1;
        }
        #pragma acc update if(n % 2 == 0) device(dev_a[n/2:n/2]) async(1)
        #pragma acc update if(n % 2 == 1) device(dev_a[(n/2+1):(n/2+1)]) async(2)
        #pragma acc wait(1,2)
        for (int x = 0; x < n/2; ++x){
            if (dev_a[x] != 1){
                err += 1;
            }
        }
        for (int x = n/2; x < n; ++x){
            if (dev_a[x] != 2){
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
#ifndef T5
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test5();
    }
    if (failed != 0){
        failcode = failcode + (1 << 4);
    }
#endif
    return failcode;
}