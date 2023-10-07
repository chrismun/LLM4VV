#ifndef T1
//T1:reduction,construct-independent,function,parallel,V:3.0-3.1
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * totals = (real_t *)malloc(10 * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 10; ++x){
        totals[x] = -99999;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copy(totals[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                real_t total = 0;
                for (int y = 0; y < n; ++y){
                    total = total + (a[x * n + y] + b[x * n + y]);
                }
                totals[x] = total;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        real_t real_totals = 0;
        for (int y = 0; y < n; ++y){
            real_totals = real_totals + a[x * n + y] + b[x * n + y];
        }
        if (fabs(totals[x] - real_totals) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:reduction,construct-independent,scalar,combined-function,parallel,V:3.0-3.1
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    int* b = (int *)malloc(2 * n * sizeof(int));
    real_t * totals = (real_t *)malloc(10 * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 2 * n; ++x){
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 10; ++x){
        totals[x] = 1;
    }

    #pragma acc data copyin(a[0:n], b[0:2*n]) copy(totals[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                real_t total = totals[x];
                #pragma acc loop reduction(*:total)
                for (int y = 0; y < n; ++y){
                    total = total - a[y];
                }
                #pragma acc loop reduction(min:total)
                for (int y = 0; y < 2 * n; ++y){
                    total = total - b[y];
                }
                totals[x] = total;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        real_t real_totals = totals[x];
        for (int y = 0; y < n; ++y){
            real_totals = real_totals - a[y];
        }
        for (int y = 0; y < 2 * n; ++y){
            real_totals = real_totals - b[y];
        }
        if (fabs(totals[x] - real_totals) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:reduction,construct-independent,scalar,combined-function,sequential,V:3.0-3.1
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    int* b = (int *)malloc(2 * n * sizeof(int));
    real_t * totals = (real_t *)malloc(10 * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 2 * n; ++x){
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 10; ++x){
        totals[x] = 1;
    }

        real_t total;
        for (int x = 0; x < 10; ++x){
            total = totals[x];
            for (int y = 0; y < n; ++y){
                total = total - a[y];
            }
            for (int y = 0; y < 2 * n; ++y){
                total = total - b[y];
            }
            totals[x] = total;
        }

    for (int x = 0; x < 10; ++x){
        real_t real_totals = 1;
        for (int y = 0; y < n; ++y){
            real_totals = real_totals - a[y];
        }
        for (int y = 0; y < 2 * n; ++y){
            real_totals = real_totals - b[y];
        }
        if (fabs(totals[x] - real_totals) > PRECISION){
            err += 1;
            break;
        }
    }
        return err;
}
#endif

#ifndef T4
//T4:reduction,construct-independent,scalar,function,parallel,V:3.0-3.1
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t totals[10];

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 2 * n; ++x){
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 10; ++x){
        totals[x] = 1;
    }

    #pragma acc data copyin(a[0:n], b[0:2*n]) copy(totals[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                real_t total = totals[x];
                #pragma acc loop reduction(*:total)
                for (int y = 0; y < n; ++y){
                    total = total * a[y];
                }
                #pragma acc loop reduction(*:total)
                for (int y = 0; y < 2 * n; ++y){
                    total = total * b[y];
                }
                totals[x] = total;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        real_t real_totals = 1;
        for (int y = 0; y < n; ++y){
            real_totals = real_totals * a[y];
        }
        for (int y = 0; y < 2 * n; ++y){
            real_totals = real_totals * b[y];
        }
        if (fabs(totals[x] - real_totals) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:reduction,construct-independent,scalar,function,sequential,V:3.0-3.1
int test5(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t totals[10];

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 2 * n; ++x){
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 10; ++x){
        totals[x] = 1;
    }


        real_t total;
        for (int x = 0; x < 10; ++x){
            total = totals[x];
            for (int y = 0; y < n; ++y){
                total = total * a[y];
            }
            for (int y = 0; y < 2 * n; ++y){
                total = total * b[y];
            }
            totals[x] = total;
        }

    for (int x = 0; x < 10; ++x){
        real_t real_totals = 1;
        for (int y = 0; y < n; ++y){
            real_totals = real_totals * a[y];
        }
        for (int y = 0; y < 2 * n; ++y){
            real_totals = real_totals * b[y];
        }
        if (fabs(totals[x] - real_totals) > PRECISION){
            err += 1;
            break;
        }
    }
        return err;
}
#endif

#ifndef T6
//T6:reduction,construct-independent,scalar,remote-device,combined-function,V:3.0-3.1
int test6(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * totals = (real_t *)malloc(10 * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 10; ++x){
        totals[x] = -99999;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) create(totals[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                real_t total = 0;
                for (int y = 0; y < n; ++y){
                    total = total + (a[x * n + y] + b[x * n + y]);
                }
                totals[x] = total;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        real_t real_totals = 0;
        for (int y = 0; y < n; ++y){
            real_totals = real_totals + a[x * n + y] + b[x * n + y];
        }
        if (fabs(totals[x] - real_totals) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T7
//T7:reduction,construct-independent,scalar,unknown,combined-function,V:3.0-3.1
int test7(){
    int err = 0;
    real_t a = 10, b = 5, total = 0;

    total = total + (a / b);

    if (fabs(total - 2) > PRECISION){
        err += 1;
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
#ifndef T6
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test6();
    }
    if (failed != 0){
        failcode = failcode + (1 << 5);
    }
#endif
#ifndef T7
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test7();
    }
    if (failed != 0){
        failcode = failcode + (1 << 6);
    }
#endif
    return failcode;
}