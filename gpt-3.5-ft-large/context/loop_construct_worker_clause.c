#ifndef T1
//T1:loop,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copy(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop worker
            for (int x = 0; x < n; ++x){
                a[x] += b[x] + c[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] + c[x])) > 2*PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:loop,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copy(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel loop worker
        for (int x = 0; x < n; ++x){
            a[x] += b[x] + c[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] + c[x]))){

    err = 1;

        }
    }

    return err;
}
#endif

#ifndef T3
//T3:loop,construct-independent,reference-counting,devonly,devonly-independent,V:2.5-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *c = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *a_host = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *b_host = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *c_host = (real_t *)malloc(10 * n * sizeof(real_t));
    int *devtest = (int *)malloc(sizeof(int));

    devtest[0] = 0;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 1;
    }

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 10 * n; ++x){
        a_host[x] = 0;
        b_host[x] = b[x];
        c_host[x] = c[x];
    }

    #pragma acc data copy(a[0:10*n], b[0:10*n], c[0:10*n])
    {
        for (int x = 0; x < 10; ++x){
            #pragma acc parallel loop worker
            for (int y = 0; y < n; ++y){
                a[x * n + y] += b[x * n + y] + c[x * n + y];
            }
        }
    }

    if (devtest[0] == 1){
        for (int x = 0; x < 10 * n; ++x){
            if (fabs(a[x] - a_host[x]) > 2*PRECISION){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:loop,construct-independent,devonly,reference-counting,V:2.5-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t *c = (real_t *)malloc(10 * n * sizeof(real_t));
    int *devtest = (int *)malloc(sizeof(int));
    devtest[0] = 0;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 1;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < 10 * n; ++x){
            a[x] = 0;
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = rand() / (real_t)(RAND_MAX / 10);
        }

        #pragma acc data copy(a[0:10*n], b[0:10*n], c[0:10*n])
        {
            for (int x = 0; x < 10; ++x){
                #pragma acc parallel loop worker
                for (int y = 0; y < n; ++y){
                    a[x * n + y] += b[x * n + y] + c[x * n + y];
                }
            }
            #pragma acc exit data copyout(a[0:10*n]) delete(b[0:10*n], c[0:10*n])
        }

        for (int x = 0; x < 10 * n; ++x){
            a[x] = 0;
        }

        for (int x = 0; x < 10; ++x){
            for (int y = 0; y < n; ++y){
                a[x * n + y] += b[x * n + y] + c[x * n + y];
            }
        }

        for (int x = 0; x < 10 * n; ++x){
            if (fabs(a[x]) > 2*PRECISION){
                err += 1;
            }
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
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