#ifndef T1
//T1:runtime,update,syntatic,V:2.5-3.2
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * b_host = (real_t *)malloc(n * sizeof(real_t));
    int * dev_test = (int *)malloc(sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        a_host[x] = a[x];
        b_host[x] = b[x];
    }

    #pragma acc enter data copyin(a[0:n], b[0:n])

    #pragma acc data present(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] + b[x];
            }
        }
        acc_update_host(a[0:n * sizeof(real_t)]);
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (a_host[x] + b_host[x])) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:n], b[0:n])

    return err;
}
#endif

#ifndef T2
//T2:runtime,update,syntatic,V:2.5-3.2
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    int * dev_test = (int *)malloc(sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data create(a[0:n], b[0:n])

    #pragma acc data present(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] - b[x];
            }
        }
        acc_update_device(a[0:n * sizeof(real_t)]);
    }

    #pragma acc exit data copyout(a[0:n], b[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (a_host[x] - b[x]))) {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,update,syntatic,V:2.5-3.2
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    int * dev_test = (int *)malloc(sizeof(int));

    dev_test[0] = 1;
    #pragma acc enter data copyin(dev_test[0:1])
    #pragma acc parallel present(dev_test[0:1])
    {
        dev_test[0] = 0;
    }

    if (dev_test[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
        }

        #pragma acc enter data create(a[0:n], b[0:n])

        #pragma acc data present(a[0:n], b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = a[x] + b[x];
                }
            }
            acc_update_self(a[0:n * sizeof(real_t)]);
        }

        #pragma acc exit data copyout(a[0:n], b[0:n])

        for (int x = 0; x < n; ++x){
    if (fabs(a[x] - a_host[x]) > (2 * PRECISION)){
                err += 1;
            }
        }
    }
    return err;
}
#endif

#ifndef T4
//T4:runtime,update,syntatic,V:2.5-3.2
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    int * dev_test = (int *)malloc(sizeof(int));

    dev_test[0] = 1;
    #pragma acc enter data copyin(dev_test[0:1])
    #pragma acc parallel present(dev_test[0:1])
    {
        dev_test[0] = 0;
    }

    if (dev_test[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
        }

        #pragma acc enter data create(a[0:n], b[0:n])

        #pragma acc data present(a[0:n], b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = a[x] - b[x];
                }
            }
            acc_update_devicet(a[0:n * sizeof(real_t)])(a[0:n * sizeof(real_t)]);
        }

        #pragma acc exit data copyout(a[0:n], b[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - (a_host[x] - b[x]))) {
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