#ifndef T1
//T1:declare,data,executable,reference-counting,create,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copy(c[0:n])
    {
        #pragma acc declare create(a[0:n], b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = a[x] + b[x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:declare,data,executable,reference-counting,V:2.5-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copy(c[0:n])
    {
        #pragma acc declare create(a[0:n], b[0:n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
        #pragma acc exit data copyout(a[0:n], b[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:declare,data,executable,reference-counting,create,V:2.5-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t)));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copy(c[0:n])
    {
        #pragma acc declare create(a[0:n], b[0:n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x;){
                c[x] = a[x] + b[x];
            }
        }
        #pragma exit(data) copyout(a[0:n], b[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:declare,data,executable,reference-counting,create,V:2.5-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    int* devtest = (int *)malloc(sizeof(int));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    if (devtest[0] == 1){
        #pragma acc data copy(c[0:n])
        {
            #pragma acc declare create(a[0:n], b[0:n])
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] = a[x] + b[x];
                }
            }
        }

        for (int x = 0; x < n; ++x){
            if (fabs(c[x]) > PRECISION){
                err = 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:declare,data,executable,reference-counting,create,V:2.5-2.7
int test5(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copy(c[0:n])
    {
        #pragma acc update device(c[0:n])
        #pragma acc declare create(a[0:n], b[0:n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])))  > PRECISION){
            err = 1;
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
        failed += test1();
    }
    if (failed){
        failcode += (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test2();
    }
    if (failed){
        failcode += (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test3();
    }
    if (failed){
        failcode += (1 << 2);
    }
#endif
#ifndef T4
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test4();
    }
    if (failed){
        failcode += (1 << 3);
    }
#endif
#ifndef T5
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test5();
    }
    if (failed){
        failcode += (1 << 4);
    }
#endif
    return failcode;
}
};
#endif

#ifndef T2
//T2:declare,data,executable,reference-counting,V:2.5-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copy(c[0:n])
    {
        #pragma acc enter data create(a[0:n], b[0:n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])))  > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed){
        failcode += (1 << 0);
    }

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test2();
    }
    if (failed){
        failcode += (1 << 1);
    }
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test3();
    }
    if (failed){
        failcode += (1 << 2);
    }
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test4();
    }
    if (failed){
        failcode += (1 << 3);
    }

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test5();
    }
    if (failed){
        failcode += (1 << 4);
    }
    
    return failcode;
}