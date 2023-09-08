#ifndef T1
//T1:compiling
int test1(){
    int err = 0;
    int host[10];
    real_t dev = 0;

    for (int x = 0; x < n; ++x){
        host[x] = 1;
    }

    #pragma acc parallel copy(dev) create(err) wait(host: n)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            dev += .1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(host[x] - (1 + .1 * x)) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:compiling, compute construct with two items
int test2(){
    int err = 0;
    int host[10];
    real_t dev = 0;

    for (int x = 0; x < n; ++x){
        host[x] = 1;
    }

    #pragma acc parallel copy(host[0:n], dev) wait(host[0:n]) num_gangs(1), num_workers(1)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            dev += .1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(host[x] - (1 + .1 * x)) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:compiling, compute construct with two items
int test3(){
    int err = 0;
    int host[10];
    real_t dev = 0;

    for (int x = 0; x < n; ++x){
        host[x] = 1;
    }

    // This test has a race condition
    #pragma acc parallel copy(host[0:n], dev) wait(dev) num_gangs(1), num_workers(1)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            dev += 1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(host[x] - (1 + .1 * x)) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:compiling, reduction, compute construct with two items
int test4(){
    int err = 0;
    int host[10];
    real_t dev = 0;

    for (int x = 0; x < n; ++x){
        host[x] = 1;
    }

    #pragma acc parallel copy(host[0:n]) reduction(+:dev) wait(host[0:n]) num_gangs(1), num_workers(1)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            dev += .1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(host[x] - 1) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:compiling, reduction, compute construct with two items
int test5(){
    int err = 0;
    int host[10];
    real_t dev[10];

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < 10; ++y){
            host[y] = 1;
            dev[y * 10 + y] = y;
        }
    }

    for (int x = 0; x < 10; ++x){
    #pragma acc parallel copy(dev[x * 10:10]) wait(dev[x * 10:10]) num_gangs(1), num_workers(1)
    {
        #pragma acc loop
        for (int y = 0; y < 10; ++y){
            dev[x * 10 + y] += .1;
        }
    }
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < 10; ++y){
            if (fabs(dev[x * 10 + y] - (y != x ? y : y + .1)) > PRECISION){
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