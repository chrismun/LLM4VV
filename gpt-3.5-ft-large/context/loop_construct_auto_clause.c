#ifndef T1
//T1:loop,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(100 * n * sizeof(real_t));

    for (int x = 0; x < 100 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:100*n], b[0:100*n]) copyout(c[0:100*n])
    {
        #pragma acc kernels
        {
            #pragma acc loop gang worker vector auto
            for (int x = 0; x < 100 * n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < 100 * n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:loop,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(100 * n * sizeof(real_t));

    for (int x = 0; x < 100 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:100*n], b[0:100*n]) copyout(c[0:100*n])
    {
        #pragma acc kernels
        {
            #pragma acc loop gang worker vector auto
            for (int x = 0; x < 100 * n; ++x){
                c[x] = a[x] + b[x];
            }
            #pragma acc loop gang worker vector
            for (int x = 0; x < 100 * n; ++x){
                c[x] += 1;
            }
        }
    }

    for (int x = 0; x < 100 * n; ++x){
        if (fabs(c[x] - (a[x] + b[x] + 1)) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:loop,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(100 * n * sizeof(real_t));

    for (int x = 0; x < 100 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:100*n], b[0:100*n]) copyout(c[0:100*n])
    {
        #pragma acc kernels
        {
            #pragma acc loop gang worker vector
            for (int x = 0; x < 100 * n; ++x){
                c[x] = a[x] + b[x];
            }
            #pragma acc loop gang worker vector auto
            for (int x = 0; x < 100 * n; ++x){
                c[x] += 1;
            }
        }
    }

    for (int x = 0; x < 100 * n; ++x){
        if (fabs(c[x] - (a[x] + b[x] + 1)) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:loop,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(100 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(100 * n * sizeof(real_t));
    int isequal = 1;

    for (int x = 0; x < 100 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = a[x] + b[x];
    }

    #pragma acc data copyin(a[0:100*n], b[0:100*n]) copyout(c[0:100*n])
    {
        #pragma acc kernels
        {
            #pragma acc loop gang worker vector auto
            for (int x = 0; x < 100 * n; ++x){
                c[x] += 1;
            }
        }
    }

    for (int x = 0; x < 100 * n; ++x){
        if (fabs(c[x] - (a[x] + b[x] + 1)) > PRECISION * 10){
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