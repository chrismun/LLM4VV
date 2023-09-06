#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_device_ptr;
    real_t *b_device_ptr;
    real_t *c_device_ptr;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }


    #pragma acc enter data create(a[0:n], b[0:n], c[0:n])

    a_device_ptr = (real_t *) acc_deviceptr(a);
    b_device_ptr = (real_t *) acc_deviceptr(b);
    c_device_ptr = (real_t *) acc_deviceptr(c);

    #pragma acc data deviceptr(a, b, c, a_device_ptr, b_device_ptr, c_device_ptr)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a_device_ptr[x] = a[x];
                b_device_ptr[x] = b[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c_device_ptr[x] = a_device_ptr[x] + b_device_ptr[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = c_device_ptr[x];
            }
        }
    }
    #pragma acc exit data copyout(a[0:n], b[0:n], c[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION) {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a;
    real_t * a_ptr;
    a = (real_t *)malloc(n * sizeof(real_t));
    for (int x = 0; x < n; ++x){
        a[x] = 1;
    }

    #pragma acc enter data copyin(a[0:n])
    a_ptr = (real_t *) acc_deviceptr(a);
    if (a[0] - a_ptr[0] > PRECISION){
        err += 1;
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime.D,R:devonly,construct-independent,reference-counting,V:2.5-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_ptr;
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * b_ptr;

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 2;
    }

    #pragma acc enter data create(a[0:n], b[0:n])
    a_ptr= (real_t *)acc_deviceptr(a);
    b_ptr = (real_t *)acc_deviceptr(b);

    #pragma acc update device(a[0:n], b[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - 1) > PRECISION){
            err += 1;
        }
        if (fabs(b[x] - 2) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:runtime,devonly,construct-independent,reference-counting,V:2.5-2.7
int test4(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    int *devtest = (int *)malloc(sizeof(int));
    real_t *a_device;
    real_t *b_device;

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel
    {
        if (acc_get_device_type() == acc_device_none){
            devtest[0] = 0;
        }
    }
    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = 1;
            b[x] = 1;
        }
        a_device = a;
        b_device = b;

        #pragma acc enter data copyin(a[0:n], b[0:n])
        a_device = (real_t *)acc_deviceptr(a);
        b_device = (real_t *)acc_deviceptr(b);
        if (a_device == a || b_device == b){
            err += 1;
        }

        #pragma acc exit data copyout(a[0:n], b[0:n])
        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - 1) > PRECISION){
                err += 1;
            }
            if (fabs(b[x] - 1) > PRECISION){
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