#ifndef T1
//T1:runtime,data,executable-data,construct-independent,reference-counting,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t * g = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    acc_copyin(c, n * sizeof(real_t));
    #pragma acc data copy(d[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - d[x]) > PRECISION){
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
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t * g = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(c[0:n])
    #pragma acc data copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }
    acc_copyin(c, n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 2;
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
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t * g = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    acc_create(c, n * sizeof(real_t));

    #pragma acc data copyin(a[0:n], b[0:n]) present(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        c[x] = 0;
    }

    #pragma acc exit data copyout(c[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 4;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:runtime,data,executable-data,construct-independent,reference-counting,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t * g = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data create(c[0:n])
    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] * b[x];
            }
        }
    }
    acc_copyin(c, n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] * b[x]))) {
            err += 8;
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:runtime,data,executable-data,construct-independent,reference-counting,V:2.0-2.7
int test5(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t * g = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    acc_create(c, n * sizeof(real_t));
    acc_copyin(c, n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
            }
        }
    }

    #pragma acc exit data copyout(c[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x]))) {
            err += 16;
        }
    }

    return err;
}
#endif

#ifndef T6
//T6:runtime,data,executable-data,reference-counting,devonly,V:2.0-2.7
int test6(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }
    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
        }

        #pragma acc enter data create(c[0:n], d[0:n])
        for (int x = 0; x < n; ++x){
            c[x] = 1;
            d[x] = 0;
        }
        for (int x = 0; x < n; ++x){
            c[x] = a[x];
            d[x] = b[x];
        }
        acc_copyin(c, n * sizeof(real_t));
        acc_copyin(d, n * sizeof(real_t));

        #pragma acc data copyin(c[0:n], d[0:n]) copyout(c[0:n], d[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] += d[x];
                    d[x] += c[x];
                }
            }
        }

        #pragma acc exit data copyout(c[0:n], d[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - (a[x] + b[x])) > PRECISION * 2){
                err += 32;
            }
            if (fabs(d[x] - (c[x] + b[x])) > PRECISION * 2){
                err += 32;
            }
        }

    }

    return err;
}
#endif

#ifndef T7
//T7:runtime,data,executable-data,reference-counting,devonly,V:2.0-2.7
int test7(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    real_t * c = (real_t *)malloc(n * sizeof(real_t)));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }
    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
        }

        #pragma acc enter data create(c[0:n], d[0:n], abase[0:n])
        #pragma acc enter data create(c[0:n], d[0:n]) copyin(a[0:n], b[0:n])
        for (int x = 0; x < n; ++x){
            c[x] = 0;
            d[x] = 0;
        }

        #pragma acc data copyin(c[0:n], d[0:n])
        {
            for (int x = 0; x < n; ++x){
                c[x] = a[x];
                d[x] = b[x];
            }

            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    c[x] += d[x];
                }
            }

        }

        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - (a[x] + b[x]))) {
                err += 64;
            }
        }

        #pragma acc exit data delete(c[0:n], d[0:n]) copyout(abase[0:n])
        #pragma acc exit data delete(c[0:n], d[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(abase[x] - (a[x] + b[x]))) {
                err += 64;
            }
        }
    }

    return err;
}