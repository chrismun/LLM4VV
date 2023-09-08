#ifndef T1
//T1:reduction,loop,combined-constructs,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t avg = 0.0;

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copy(avg)
    {
        #pragma acc parallel loop reduction(+:avg)
        for (int x = 0; x < 10 * n; ++x){
            avg += a[x] * b[x];
        }
    }
    avg = avg / (n * 10);
    real_t sum = 0.0;

    for (int x = 0; x < 10 * n; ++x){
        sum += a[x] * b[x];
    }
    sum = sum / (n * 10);

    if (fabs(sum - avg) > (2.0 / n) && sum != avg){
        err = 1;
    }

    return err;
}
#endif

#ifndef T2
//T2:reduction,loop,combined-constructs,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(25 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(25 * n * sizeof(real_t));
    real_t avg[5];

    for (int x = 0; x < 25 * n; ++x){
        a[x] = 1;
        b[x] = 1;
    }

    for (int x = 0; x < 5; ++x){
        avg[x] = 0.0;
    }

    #pragma acc data copyin(a[0:25*n], b[0:25*n]) copy(avg[0:5])
    {
        #pragma acc parallel loop num_gangs(5) reduction(+:avg)
        for (int x = 0; x < 5 * n; ++x){
            avg[x%5] += a[x] * b[x];
        }
    }

    for (int x = 0; x < 25 * n; ++x){
        if (fabs(a[x]*b[x] - (1 + avg[x%5])) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:reduction,loop,combined-constructs,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(25 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(25 * n * sizeof(real_t));
    real_t avg[5];

    for (int x = 0; x < 25 * n; ++x){
        a[x] = 1;
        b[x] = 1;
    }

    for (int x = 0; x < 5; ++x){
        avg[x] = 0.0;
    }

    #pragma acc data copyin(a[0:25*n], b[0:25*n]) copy(avg[0:5])
    {
        #pragma acc parallel loop reduction(+:avg)
        for (int x = 0; x < 5 * n; ++x){
            avg[x%5] += a[x] * b[x];
        }
    }

    for (int x = 0; x < 5; ++x){
        avg[x] = avg[x] / 5 / n;
    }

    for (int x = 0; x < 5 * n; ++x){
        if (fabs(avg[x%5] - 1) > PRECISION){
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
    return failcode;
}