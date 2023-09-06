#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
    real_t * random = (real_t *)malloc(1 * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = 0;
        d[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n], d[0:n])

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
        d[x] = 0;
    }

    #pragma acc data copyin(d[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = a[x] + b[x];
            }
            #pragma acc loop
            for (int x = 1; x < n; ++x){
                d[x] = c[x] + d[x - 1];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        a_copy[x] = a[x];
    }

    acc_map_data(a, n * sizeof(real_t), a);

    if (data_present(a, n * sizeof(real_t))) {
        for (int x = 0; x < n; ++x) {
            a[x] = 0;
        }
        #pragma acc update device(a[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (a_copy[x] + b[x]))) {
            err += 1;
        }
    }

    acc_unmap_data(a);
    
    return err;
}
#endif

#ifndef T2
//T2:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
    real_t * random = (real_t *)malloc(1 * sizeof(real_t));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            random[x] = rand() / (real_t)(RAND_MAX / 10);
        }
        #pragma acc enter data copyin(random[0:1])
        *host_ptr_present = 1;
    }

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
    }

    if (data_present(a, n * sizeof(real_t))) {
        #pragma acc update self(a[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x]) > PRECISION){
            err += 1;
        }
    }

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    acc_map_data(c, n * sizeof(real_t), c);

    for (int x = 0; x < n; ++x){
        c[x] = a[x] + b[x];
    }

    #pragma acc data present(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + 2 * b[x])) > PRECISION){
            err += 1;
        }
    }

    acc_unmap_data(c);

    return err;
}
#endif

#ifndef T3
//T3:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
    real_t * random = (real_t *)malloc(1 * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n])
    #pragma acc enter data create(random[0:1])
    *host_ptr_present = 0;
    #pragma acc enter data copyin(host_ptr_present[0:1])
    *host_ptr_present = 1;

    #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = host_ptr_present[0] ? random[x] : rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0;
        }
    }

    #pragma acc exit data delete(host_ptr_present[0:1])

    for (int x = 0; x < n; ++x){
        if (*host_ptr_present == 1){
            random[x] = a[x];
        }
        a[x] = 0;
    }

    acc_map_data(a, n * sizeof(real_t), a);

    for (int x = 0; x < n; ++x){
        a_copy[x] = a[x];
        c[x] = a[x] + b[x];
    }

    acc_map_data(c, n * sizeof(real_t), c);

    #pragma acc data present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += b[x];
            }
        }
    }

    #pragma acc data copyout(a[0:n], b[0:n])
    {
        #pragma acc parallel present(a[0:n], c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = -1;
            }
        }

        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - (c[x] - b[x])) > PRECISION){
                err += 1;
            }
        }
    }

    #pragma acc exit data copyout(a[0:n], b[0:n], c[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - rand() / (real_t)(RAND_MAX / 10))) > PRECISION {
            err += 1;
        }
        if (fabs(b[x] - rand() / (real_t)(RAND_MAX / 10))) > PRECISION) {
            err += 1;
        }
    }

    acc_unmap_data(a);
    acc_unmap_data(c);

    return err;
}
#endif

#ifndef T4
//T4:runtime,data,executable-data,construct-independent,compatibility-features,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
    devtest[0] = 0;

    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 1;
    }

    if (devtest[0] == 0){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0;
        }

        #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n])
    
        #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }

        for (int x = 0; x < n; ++x){
            if (fabs(c[x]) > PRECISION){
                err += 1;
            }
        }

        #pragma acc exit data copyout(c[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - (a[x] + b[x]))) > PRECISION) {
                err += 1;
            }
        }

        acc_delete(a, n * sizeof(real_t));
        acc_delete(b, n * sizeof(real_t));
        acc_delete(c, n * sizeof(real_t));
    }

    return err;
}
#endif

#ifndef T5
//T5:runtime,data,executable-data,construct-independent,compatibility-features,V:2.0-2.7
int test5(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
    devtest[0] = 0;

    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 1;
    }

    if (devtest[0] == 0){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0;
        }

        acc_map_data(c, n * sizeof(real_t), c);

        #pragma acc enter data copyin(a[0:n], b[0:n])
    
        #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }

        for (int x = 0; x < n; ++x){
            if (fabs(c[x]) > PRECISION) {
                err += 1;
            }
        }

        acc_unmap_data(c);

        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - (a[x] + b[x]))) > PRECISION {
                err += 1;
            }
        }

        acc_delete(a, n * sizeof(real_t));
        acc_delete(b, n * sizeof(real_t)));
        
    }

    return err;
}
#endif

#ifndef T6
//T6:runtime,data,executable-data,construct-independent,compatibility-features,V:2.0-2.7
int test6(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
    devtest[0] = 0;

    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel present(devtest[0:1])
    {
        devtest[0] = 1;
    }

    if (devtest[0] == 0){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0;
        }

        #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n])
    
        *host_ptr_present = 1;
        #pragma acc enter data copyin(host_ptr_present[0:1])
        *host_ptr_present = 0;
    
        #pragma acc parallel present(host_ptr_present[0:1], a[0:n], b[0:n], c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = host_ptr_present[0] ? c[x] : a[x];
                a[x] += b[x];
            }
        }

        for (int x = 0; x < n; ++x) {
            if (fabs(a[x] - (c[x] + b[x])) > PRECISION) {
                err += 1;
            }
        }

        acc_unmap_data(c);

        for (int x = 0; x < n; ++x) {
            if (fabs(c[x] - a[x]) > PRECISION) {
                err += 1;
            }
        }
    }

    return err;
}