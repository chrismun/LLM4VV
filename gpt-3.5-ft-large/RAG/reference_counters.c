#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    size_t a_create = 0;
    size_t current_a_dynamic = 0;
    size_t b_create = 0;
    size_t current_b_dynamic = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n]) create(b[0:n])
    for (int x = 0; x < n; ++x){
        #pragma acc data present(a[0:n])
        {
            #pragma acc enter data create(a[0:n])
            #pragma acc enter data create(a[0:x+1]) //This is important.  It cannot have the possibility to create duplicated data.
            #pragma acc parallel present(a[0:n], b[0:n])
            {
                #pragma acc loop
                for (int y = 0; y <= x; ++y){
                    a[y] = a[y] + 1;
                }
                #pragma acc loop
                for (int y = x + 1; y < n; ++y){
                    b[y] = a[y] - 2;
                }
            }
            #pragma acc exit data delete(a[0:n]) if(0) //This is important.  previous data may still be present here
            #pragma acc exit data delete(a[0:x + 1]) if(0)
        }
        #pragma acc data copyout(b[0:n])
        {
            #pragma acc enter data create(a[0:n])
            #pragma acc parallel present(a[0:n], b[0:n])
            {
                #pragma acc loop
                for (int y = 0; y <= x; ++y){
                    b[y] = a[y];
                }
            }
            #pragma acc exit data copyout(a[0:n])
        }
        for (int y = 0; y <= x; ++y){
            if (fabs(a[y] - (b[y] - 1)) > PRECISION){
                err += 1;
            }
        }
        for (int y = x + 1; y < n; ++y){
            if (fabs(a[y] - (b[y] / 2)) > PRECISION){
                err += 1;
            }
        }
    }

    #pragma acc exit data copyout(a[0:n], b[0:n])

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    size_t a_create = 0;
    size_t current_a_dynamic = 0;
    size_t b_create = 0;
    size_t current_b_dynamic = 0;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc enter data create(a[0:n]) create(b[0:n])
    for (int x = 0; x < n; ++x){
        a[x] = a[x] + 1;
        a_create += 1;
    }
    #pragma acc enter data create(a[0:n]) 
    for (int x = 0; x < n; ++x){
        a[x] = a[x] + 1;
        a_create += 1;
    }
    #pragma acc enter data create(a[0:n]) create(b[0:n])
    for (int x = 0; x < n; ++x){
        a[x] = a[x] + 1;
        a_create += 1;
        b[x] = b[x] + 1;
        b_create += 1;
    }
    #pragma acc enter data create(a[0:n]) create(b[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (n + x + 1)) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data copyout(a[0:n], b[0:n]) delete(a[0:n], b[0:n])
    if (fabs(a[0] - (a[0] - n)) > PRECISION){
        err += 1;
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,reference-counting,construct-independent,devonly,V:2.5-2.7
int test3(){
    int err = 0;
    srand(SEED);
    size_t *devtest = (size_t *)malloc(sizeof(size_t));
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    int is_present = 0;

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = 0;
        }

        #pragma acc enter data create(a[0:n], b[0:n])
        for (int x = 0; x < n; ++x){
            #pragma acc enter data create(a[0:a_create])
            a[x] += 1;
            #pragma acc update device(a[0:n])
            for (int y = 0; y < x; ++y){
                if (fabs(a[y] - b[y] - 1) > 3 * PRECISION){
                    err += 1;
                }
            }
            b[x] = a[x];
        }
        a_create += 1;
        a_create -= 1;
        #pragma acc exit data copyout(a[0:n], b[0:n]) delete(a[0:n], b[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - (b[x] + 1)) > PRECISION){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:runtime,data,executable-data,reference-counting,construct-independent,devonly,V:2.5-2.7
int test4(){
    int err = 0;
    srand(SEED);
    size_t *devtest = (size_t *)malloc(sizeof(size_t));
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    int is_present = 0;

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = 0;
        }

        for (int x = 0; x < n; ++x){
            a[x] += 1;
        }
        #pragma acc enter data copyin(a[0:n], b[0:n])
        #pragma acc enter data create(a[0:n], b[0:n])
        #pragma acc parallel present(a[0:n], b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] += 1;
                b[x] = a[x];
            }
        }
        current_a_dynamic += 1;
        #pragma acc exit data copyout(a[0:n], b[0:n]])
        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - (b[x] - 2)) > PRECISION){
                err += 1;
            }
        }

        #pragma acc enter data copyin(a[0:n], b[0:n])
        #pragma acc enter data create(a[0:n], b[0:n])
        #pragma acc parallel present(a[0:n], b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] += 1;
                b[x] = a[x];
            }
        }
        current_a_dynamic += 1;
        #pragma acc exit data copyout(a[0:n], b[0:n])
        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - b[x]) > PRECISION){
                err += 1;
            }
        }
        #pragma acc exit data delete(a[0:n], b[0:n])
    }
    return err;
}
#endif

#ifndef T5
//T5:runtime,data,executable-data,reference-counting,construct-independent,devonly,V:2.5-2.7
int test5(){
    int err = 0;
    srand(SEED);
    size_t *devtest = (size_t *)malloc(sizeof(size_t));
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    int is_present = 0;

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = 0;
        }

        a_create = 1;
        #pragma acc enter data copyin(a[0:n], b[0:n])
        #pragma acc enter data create(a[0:n], b[0:n])
        for (int x = 0; x < n; ++x){
            a[x] += 1;
            b[x] += a[x];
        }
        #pragma acc exit data delete(a[0:n], b[0:n]) copyout(a[0:n], b[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - (b[x] - 1)) > PRECISION){
                err += 1;
            }
        }

        #pragma acc enter data copyin(a[0:n], b[0:n])
        #pragma acc enter data copyin(a[0:1]) create(a[0:n]) //This can potentially leak for this thread but shouldn't for the others
        for (int x = 0; x < n; ++x){
            a[x] += 1;
            b[x] += a[x];
        }
        #pragma acc exit data copyout(a[0:n], b[0:n])
        for (int x = 0; x < 2; ++x){
            if (fabs(a[x] - (b[x] - 2)) > PRECISION){
                err += 1;
            }
        }
        for (int x = 2; x < n; ++x){
            if (fabs(a[x]) > PRECISION){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T6
//T6:runtime,data,executable-data,reference-counting,construct-independent,V:2.5-2.7
int test6(){
    int err = 0;
    srand(SEED);
    size_t *devtest = (size_t *)malloc(sizeof(size_t));
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
     #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    a_create += 1;
    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc enter data create(a[0:n], b[0:n])
    a_create += 1;
    #pragma acc enter data copyin(a[0:1])
    for (int x = 0; x < n; ++x){
        a[x] += 1;
        b[x] += a[x];
    }
    #pragma acc exit data copyout(a[0:n], b[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x]) > PRECISION){
            err += 1;
        }
        if (fabs(b[x] - 2) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data copyout(a[0:n], b[0:n]) delete(a[0:n]) 

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] - 1)) > PRECISION){
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

    return failcode;
}