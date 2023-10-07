#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(time(NULL));
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a = (real_t *)acc_create_unified(NULL, n * sizeof(real_t));
    real_t * dev_b = (real_t *)acc_create_unified(NULL, n * sizeof(real_t));
    real_t * dev_c = (real_t *)acc_create_unified(NULL, n * sizeof(real_t));

    for (int x = 0; x < 128; ++x){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = 0;
            c[x] = 0;
        }
        #pragma acc enter data copyin(a[0:n], b[0:n])
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = 10;
            }
        }
        #pragma acc exit data delete(a[0:n])
        #pragma acc exit data copyout(b[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(b[x] - 10) > PRECISION){
                err += 1;
            }
        }
        #pragma acc exit data delete(b[0:n], c[0:n])
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(time(NULL));
    real_t * a = (real_t *)malloc(128 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(128 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(128 * n * sizeof(real_t));
    real_t * dev_a = (real_t *)acc_create_unified(NULL, 128 * n * sizeof(real_t));
    real_t * dev_b = (real_t *)acc_create_unified(NULL, 128 * n * sizeof(real_t));
    real_t * dev_c = (real_t *)acc_create_unified(NULL, 128 * n * sizeof(real_t));

    for (int x = 0; x < 128; ++x){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = 0;
            c[x] = 0;
        }
        for (int x = 0; x < n; ++x){
            dev_a[x + n * y] = a[x];
            dev_b[x + n * y] = 0;
            dev_c[x + n * y] = 0;
        }

        #pragma acc enter data copyin(dev_a[0:n], dev_b[0:n])
        #pragma acc kernels present(dev_b)
        {
        }

        #pragma acc exit data delete(dev_a[0:n])
        #pragma acc exit data copyout(dev_b[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(dev_b[x] - a[x]) > PRECISION){
                err += 1;
            }
        }
        #pragma acc exit data delete(dev_b[0:n], dev_c[0:n])
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test3(){
    int err = 0;
    real_t *data = (real_t *)malloc(1024 * sizeof(real_t));
    real_t *dev = (real_t *)acc_create_unified(data, 1024 * sizeof(real_t));
    for (int x = 0; x < 1024; ++x){
        data[x] = x;
    }

    for (int x = 0; x < 14; ++x){
        #pragma acc enter data present(dev[0:1024])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 1024; ++x){
                dev[x] = 0;
            }
        }
        #pragma acc exit data delete(dev[0:1024])
    }
    #pragma acc enter data copyin(dev[0:1024])

    for (int x = 0; x < 14; ++x){
        for (int x = 0; x < 1024; ++x){
            data[x] += 1E-6;
        }
        acc_copyout(dev[0:1024], 1024 * sizeof(real_t));
    }

    for (int x = 0; x < 1024; ++x){
        if (fabs(14 - data[y]) > PRECISION){
            err += 1;
            break;
        }
    }

    #pragma acc exit data delete(dev[0:1024])

    return err;
}
#endif

#ifndef T4
//T4:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test4(){
    int err = 0;
    real_t *data = (real_t *)malloc(1024 * sizeof(real_t));
    real_t *dev = (real_t *)acc_create_unified(data, 1024 * sizeof(real_t));
    for (int x = 0; x < 1024; ++x){
        data[x] = x;
    }

    for (int x = 0; x < 14; ++x){
        #pragma acc enter data present(dev[0:1024])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 1024; ++x){
                dev[x] = 0;
            }
        }
        #pragma acc exit data delete(dev[0:1024])
    }
    #pragma acc enter data copyin(dev[0:1024])

    for (int x = 0; x < 14; ++x){
        for (int x = 0; x < 1024; ++x){
            data[x] += 1E-6;
        }
        acc_delete(dev[0:1024], 1024 * sizeof(real_t));
    }
    for (int x = 0; x < 1024; ++x){
        if (fabs(data[x]) > PRECISION * 16){
            err += 1;
            break;
        }
    }

    #pragma acc exit data delete(dev[0:1024])

    return err;
}
#endif

#ifndef T5
//T5:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test5(){
    int err = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a = (real_t *)acc_create_unified(NULL, n * sizeof(real_t));
    real_t * dev_b = (real_t *)acc_create_unified(NULL, n * sizeof(real_t));
    real_t * dev_c = (real_t *)acc_create_unified(NULL, n * sizeof(real_t));

    for (int x = 0; x < 128; ++x){
        for (int x = 0; x < n; ++x){
            a[x] = 0;
            b[x] = 0;
            c[x] = 0;
        }
        #pragma acc enter data create(a[0:n], b[0:n])
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = x;
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = x;
            }
        }
        #pragma acc exit data delete(a[0:n])
        #pragma acc exit data copyout(b[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(b[x] - c[x]) > PRECISION){
                err += 1;
            }
        }
        #pragma acc exit data delete(c[0:n])
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 1; x <= NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (int x = 1; x <= NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 1; x <= NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif
#ifndef T4
    failed = 0;
    for (int x = 1; x <= NUM_TEST_CALLS; ++x){
        failed = failed + test4();
    }
    if (failed != 0){
        failcode = failcode + (1 << 3);
    }
#endif
#ifndef T5
    failed = 0;
    for (int x = 1; x <= NUM_TEST_CALLS; ++x){
        failed = failed + test5();
    }
    if (failed != 0){
        failcode = failcode + (1 << 4);
    }
#endif
    return failcode;
}