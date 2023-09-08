#ifndef T1
//T1:data,data-region,default-mapping,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t total = 0.0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = rand() / (real_t)(RAND_MAX / 10);
        f[x] = 0.0;
    }
    #pragma acc data copyin(a[0:n], b[0:n], d[0:n], e[0:n]) copyout(c[0:n], f[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                f[x] = d[x] + e[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
        if (fabs(f[x] - (d[x] + e[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2: data,data-regions,construct-independent,reference-counting,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t * devtest;
    int * devtest_counter;
    int acc_device_nvidia = 0;
    int acc_device_altera = 0;

    devtest_counter = (int *)malloc(1 * sizeof(int));
    devtest_counter[0] = 0;
    #pragma acc enter data copyin(devtest_counter[0:1])
    #pragma acc parallel present(devtest_counter[0:1])
    {
        devtest_counter[0] += 1;
    }

    if (devtest_counter[0] > 1){
        devtest = (real_t *)malloc(n * sizeof(real_t));
        #pragma acc enter data copyin(c[0:n], f[0:n]) create(a[0:n], b[0:n], d[0:n], e[0:n]) present_or_copy(a[0:n], b[0:n], d[0:n], e[0:n]:[devtest_counter[0]]), copyin(a[0:n], b[0:n], d[0:n], e[0:n]:[devtest_counter[0]]))
        #pragma acc parallel present_or_copy(c[0:n], f[0:n])
        {
            devtest_counter[0] += 1;
        }
        #pragma acc exit data copyout(devtest[0:n])
        if (devtest_counter[0] > 2){
            for (int x = 0; x < n; ++x){
                devtest[x] = rand() / (real_t) (RAND_MAX / 10);
            }
            #pragma acc enter data copyin(devtest[0:n])
            for (int x = 0; x < n; ++x){
                a[x] = devtest[x];
                b[x] = devtest[x];
                d[x] = devtest[x];
                e[x] = devtest[x];
            }
        }
    }
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 1;
    }
    for (int x = 0; x < n; ++x){
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = rand() / (real_t)(RAND_MAX / 10);
        f[x] = 2;
    }

    return err;
}
#endif

#ifndef T3
//T3: data,data-regions,construct-independent,reference-counting,V:2.0-2.7
int test3(){
    // Test with initilization of copy variable off of the device
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * devtest;
    int * devtest_counter;
    int acc_device_nvidia = 0;
    int acc_device_altera = 0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        a_copy[x] = a[x];
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc enter data copyin(c[0:n]) create(a[0:n], b[0:n]) copyin(a[0:n], b[0:n])
    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
    }
    #pragma acc data copyout(c[0:n]) copyin(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a_copy[x] + b[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4: data,data-regions,construct-independent,reference-counting,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * devtest;
    int * devtest_counter;
    int acc_device_nvidia = 0;
    int acc_device_altera = 0;

    devtest_counter = (int *)malloc(1 * sizeof(int));
    devtest_counter[0] = 0;
    #pragma acc enter data copyin(devtest_counter[0:1])
    #pragma acc parallel present(devtest_counter[0:1])
    {
        devtest_counter[0] += 1;
    }

    if (devtest_counter[0] > 1){
        devtest = (real_t *)malloc(n * sizeof(real_t));
        #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:n]) copyin(c[0:n]) present_or_copy(c[0:n])
        {
            for (int x = 0; x < n; ++x){
                c[x] = 0;
            }
        }
        #pragma acc exit data copyout(a[0:n], b[0:n], c[0:n]) 
        if (devtest_counter[0] > 2){
            for (int x = 0; x < n; ++x){
                a[x] = rand() / (real_t)(RAND_MAX / 10);
                b[x] = rand() / (real_t)(RAND_MAX / 10);
            }
        }
        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - (a[x] * .5)) > PRECISION){
                err += 1;
            }
            if (fabs(b[x] - (b[x] * .5)) > PRECISION){
                err += 1;
            }
            if (fabs(c[x]) > PRECISION){
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
    return failcode;
}