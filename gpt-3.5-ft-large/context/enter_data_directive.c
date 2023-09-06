#ifndef T1
//T1:enter-data,data-region,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(a[0:n]) 

    for (int x = 0; x < n; ++x){
        a[x] = b[x];
    }

    #pragma acc exit data delete(a[0:n]) 

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:enter-data,data-region,devonly,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int host = 1;
    int dev = 0;

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    for (int x = 0; x < n; ++x){
        a[x] = b[x];
    }

    #pragma acc enter data copyin(a[0:n]) 

    #pragma acc data copyin(c[0:n]) present(a[0:n])
    {
        #pragma acc parallel
        {
            for (int x = 0; x < n; ++x){
                a[x] += c[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] + c[x])) > PRECISION){
            err = 1;
        }
    }

    #pragma acc exit data delete(a[0:n])

    return err;
}
#endif

#ifndef T3
//T3:enter-data,data-region,present-update,devonly,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = 0.0;
            b[x] = rand() / (real_t)(RAND_MAX / 10);
        }

        #pragma acc enter data copyin(a[0:n])

        for (int x = 0; x < n; ++x){
            a[x] += b[x];
        }

        #pragma acc enter data copyin(a[0:n])

        for (int x = 0; x < n; ++x){
            a[x] += b[x];
        }

        #pragma acc exit data copyout(a[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - (b[x] * 2)) > PRECISION){
                err = 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:enter-data,data-region,present-update,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(a[0:n])

    for (int x = 0; x < n; ++x){
        a[x] += b[x];
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc data copyin(b[0:n]) present(a[0:n])
    {
        #pragma acc parallel
        {
            for (int x = 0; x < n; ++x){
                a[x] += b[x];
            }
        }
    }

    #pragma acc exit data copyout(a[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] * 2)) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:enter-data,data-region,devonly,V:2.0-2.7
int test5(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = 0.0;
            b[x] = rand() / (real_t)(RAND_MAX / 10);
        }

        #pragma acc enter data copyin(a[0:n])

        #pragma acc enter data copyin(a[0:n])

        #pragma acc data copyin(b[0:n]) present(a[0:n])
        {
            #pragma acc parallel
            {
                for (int x = 0; x < n; ++x){
                    a[x] += b[x];
                }
            }
        }

        #pragma acc exit data copyout(a[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(a[x]) > PRECISION){
                err = 1;
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