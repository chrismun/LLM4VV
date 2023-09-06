#ifndef T1
//T1:runtime,data,executable-data,construct-independent,reference-counting,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int* devtest = (int *)malloc(sizeof(real_t) * n);

    for (int x = 0; x < n; ++x){
        devtest[x] = 0;
    }

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:n])
    #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n]) copyout(c[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,reference-counting,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int) * n);

    for (int x = 0; x < n; ++x){
        devtest[x] = 0;
    }

    int is_dev = 1;
    #pragma acc parallel 
    {
        is_dev = 1;
    }

    for (int x = 0; x < n; ++x){
        if (devtest[x] == is_dev){
            devtest[x] = 1;
        }
    }

    for (int x = 1; x < n; ++x){
        if (devtest[x] == devtest[0]){
            for (int y = 0; y < x; ++y){
                if (devtest[y] != devtest[x]){
                    break;
                    err += 2;
                }
            }
        }
    }

    #pragma acc enter data create(a[0:n], b[0:n], devtest[0:n]) copyin(devtest[0:n])
    #pragma acc parallel present(a[0:n], b[0:n], devtest[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            devtest[x] = is_dev;
        }
    }
    #pragma acc exit data delete(devtest[0:n]) copyout(a[0:n], b[0:n])

    for (int x = 0; x < n; ++x){
        if (devtest[x] + 1 == is_dev){
            if (fabs(a[x] - b[x]) > PRECISION){
                err += 1;
            }
        }
        else{
            if (fabs(a[x] - (b[x] + a[x]))) {
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,construct-independent,reference-counting,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int) * 5);
    int total;

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 2;
    }

    total = 0;
    while (devtest[0] == 2){
       total += 1; 
       #pragma acc update device(devtest[0:1])
    }

    if (total == 0){
        return 1;
    }
    if (devtest[0] != 1){
        return 1;
    }

    for (int x = 0; x < n; ++x){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0;
        }

        for (int x = 0; x < 3; ++x){
            devtest[x] = 0;
        }

        #pragma acc enter data create(a[0:n], b[0:n], devtest[0:3])
        for (int x = 0; x < n; ++x){
            if (a[x] > b[x]) {
                #pragma acc enter data copyin(devtest[x:1])
                #pragma acc parallel present(a[0:n], devtest[x:1])
                {
                    a[x] = 0;
                    devtest[x] = 1;
                }
                #pragma acc end data
                #pragma acc enter data copyin(b[x:1])
                #pragma acc parallel present(b[0:n], devtest[x:1])
                {
                    b[x] = 0;
                }
                #pragma acc end data
            }
        }

        #pragma acc parallel copyin(a[0:n], b[0:n]) present(devtest[0:n]) present(c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                if (devtest[x] == 1){
                    c[x] = a[x];
                }
                else {
                    c[x] = b[x];
                }
            }
        }

        #pragma acc exit data delete(a[0:n], b[0:n], devtest[0:3]) copyout(c[0:n])

        for (int x = 0; x < n; ++x){
            if (devtest[x] == 1){
                if (fabs(c[x] - a[x]) > PRECISION){
                    err += 1;
                }
            }
            else {
                if (fabs(c[x] - b[x]) > PRECISION){
                    err += 1;
                }
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:runtime,data,construct-independent,reference-counting,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int ac = 0;
    int bc = 0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc enter data create(a[0:n], b[0:n], ac, bc)
    #pragma acc parallel present(a[0:n], b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            ac = 1;
            bc = 1;
        }
    }
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n])
    #pragma acc exit data copyout(c[0:n]) delete(a[0:n], b[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x]))) {
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