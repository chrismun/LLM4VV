#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.7-3.2
int test1(){
    int err = 0;
    real_t *a = (real_t *)acc_malloc(n * sizeof(real_t));

    srand(SEED);

    for (int x = 0; x < n; ++x){
        a[x] = 3.0;
    }
    #pragma acc data copy(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] / 1.5;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - 2.0) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,V:2.7-3.2
int test2(){
    int err = 0;
    real_t *a;
    int found_device = 0;

    a = (real_t *)acc_malloc_test(n * sizeof(real_t)));

    if (a == NULL){
        return 1;
    }

    #pragma acc enter data create(a[0:n])

    #pragma acc parallel present(a[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = 1.0;
        }
    }

    for (int x = 0; x < n; ++x){
            a[x] = 2.0;
    }

    #pragma acc exit data copyout(a[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - 2.0) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,devonly,construct-independent,EMISSIONS_CHECK
int test3(){
    int err = 0;
    real_t * a = (real_t *)acc_malloc(n * sizeof(real_t)));

    if (acc_get_device_type() != acc_device_none){
        acc_map_data(a, n * sizeof(real_t));
    }

    acc_free(a, n * sizeof(real_t)),

    return err;
}
#endif

#ifndef T4
//T4:runtime,data,executable-data,devonly,construct-independent,EMISSIONS_CHECK
int test4(){
    int err = 0;
    real_t* a = (real_t *)acc_malloc(n * sizeof(real_t)));

    #pragma acc enter data copyin(a[0:n])
    #pragma acc exit data delete(a[0:n])

    return err;
}
#endif

#ifndef T5
//T5:runtime,data,executable-data,construct-independent,V:2.7-3.2
int test5(){
    int err = 0;
    real_t * a;
    real_t * b;
    int * hasDevice = (int *)malloc(sizeof(int));

    hasDevice[0] = 1;
    #pragma acc enter data copyin(hasDevice[0:1])
    #pragma acc exit data copyout(hasDevice[0:1])

    if (hasDevice[0] == 0){
        return err;
    }

    a = (real_t *)acc_malloc(n * sizeof(real_t)));
    b = (real_t *)acc_malloc(n * sizeof(real_t)));

    if (a == NULL || b == NULL){
        return 1;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc parallel
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = a[x] * a[x];
        }
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            b[x] = a[x] + a[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (a[x] + a[x])) > PRECISION){
            err = 1;
        }
    }

    #pragma acc exit data delete(a[0:n], b[0:n])

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