#ifndef T1
//T1:parallel,num_gangs,positive
int test1(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict d = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c_host = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 5;
        d[x] = 0;
        a_host[x] = a[x];
        b_host[x] = b[x];
        c_host[x] = c[x];
    }

    #pragma acc data copyin(a[0:n], b[0:n], c[0:n]) copyout(d[0:n])
    {
        #pragma acc parallel num_gangs(10*HAFTEN)
        {
            #pragma acc loop gang
            for (int x = 0; x < 10; ++x){
                #pragma acc loop worker
                for (int y = 0; y < HAFTEN; ++y){
                    d[x * HAFTEN + y] = a[x * HAFTEN + y] + b[x * HAFTEN + y] + c[x * HAFTEN + y];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(d[x] - (a[x] + b[x] + c[x])) > PRECISION){
            err += 1;
        }
    }
    
    for (int x = 0; x < n; ++x){
        if (a[x] - a_host[x] > PRECISION){
            err += 1;
        }
        if (b[x] - b_host[x] > PRECISION){
            err += 1;
        }
        if (c[x] - c_host[x] > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:parallel,kernels,num_gangs,positive
int test2(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict d = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict b_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * restrict c_host = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 5;
        d[x] = 0;
        a_host[x] = a[x];
        b_host[x] = b[x];
        c_host[x] = c[x];
    }

    #pragma acc data copyin(a[0:n], b[0:n], c[0:n]) copyout(d[0:n])
    {
        #pragma acc kernels loop num_gangs(16)
        for (int x = 0; x < n; ++x){
            d[x] = a[x] + b[x] + c[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(d[x] - (a[x] + b[x] + c[x])) > PRECISION){
            err += 1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (a[x] - a_host[x] > PRECISION){
            err += 1;
        }
        if (b[x] - b_host[x] > PRECISION){
            err += 1;
        }
        if (c[x] - c_host[x] > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:parallel,kernels,async,num_gangs,positive
int test3(){
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict d = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict a_host = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict b_host = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict c_host = (real_t *)malloc(2 * n * sizeof(real_t));
    int * async = (int *)malloc(sizeof(int));

    for (int x = 0; x < 2 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 5;
        d[x] = 0;
        a_host[x] = a[x];
        b_host[x] = b[x];
        c_host[x] = c[x];
    }
    for (int x = 0; x < ASYNC_NUM; ++x) {
        #pragma acc enter data create(a[0:2*n], b[0:2*n], c[0:2*n]) async(x+1)
        async[x] = x + 1;
    }

    #pragma acc data copyin(a[0:2*n], b[0:2*n], c[0:2*n]) copyout(d[0:2*n])
    {
        #pragma acc parallel loop num_gangs(10*HAFTEN) async(1)
        for (int x = 0; x < 10; ++x) {
            for (int y = 0; y < HAFTEN; ++y) {
                c[x * HAFTEN + y] = c[x * HAFTEN + y] + 1;
            }
        }
        #pragma acc kernels loop num_gangs(16) async(2)
        for (int x = 0; x < 2 * n; ++x) {
            d[x] = a[x] + b[x] + c[x];
        }
        #pragma acc parallel loop num_gangs(10*HAFTEN) async(1)
        for (int x = 0; x < 10; ++x) {
            for (int y = 0; y < HAFTEN; ++y) {
                d[x * HAFTEN + y] += 1;
            }
        }
    }
    #pragma acc exit data copyout(a[0:2*n], b[0:2*n], c[0:2*n]) async(1, 2)
    for (int x = 0; x < 2 * n; ++x) {
        if (fabs(d[x] - (a[x] + b[x] + c[x])) > PRECISION) {
            err += 1;
        }
    }

    for (int x = 0; x < 2 * n; ++x) {
        if (a[x] - a_host[x] > PRECISION) {
            err += 1;
        }
        if (b[x] - b_host[x] > PRECISION) {
            err += 1;
        }
        if (c[x] - (c_host[x] + 2) > PRECISION) {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:kernels,async,devonly,illegal,construct-independent,V:2.0-2.7
int test4() {
    int err = 0;
    srand(SEED);
    real_t * restrict a = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict b = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict c = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict a_copy = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict b_copy = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t * restrict c_copy = (real_t *)malloc(2 * n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));

    devtest[0] = 1;
    #pragma acc enter data copyin(devtest[0:1])
    #pragma acc parallel
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < 2 * n; ++x) {
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0;
            a_copy[x] = a[x];
            b_copy[x] = b[x];
            c_copy[x] = c[x];
        }

        #pragma acc data copyin(a[0:2*n], b[0:2*n]) copyout(c[0:2*n])
        {
            for (int x = 0; x < 2 * n; ++x) {
                c[x] = 25;
            }
            #pragma acc kernels loop num_gangs(2) independent async(4)
            for (int x = 0; x < n; ++x) {
                c[x] = a[x] + b[x];
            }
            #pragma acc kernels loop num_gangs(2) independent async(4)
            for (int x = 0; x < n; ++x) {
                c[n + x] = a[x] + b[x];
            }
        }

        for (int x = 0; x < 2 * n; ++x) {
            if (fabs(c[x] - (a[x] + b[x] + 25)) > PRECISION) {
                err += 1;
            }
        }

        for (int x = 0; x < 2 * n; ++x) {
            if (a[x] - a_copy[x] > PRECISION) {
                err += 1;
            }
            if (b[x] - b_copy[x] > PRECISION) {
                err += 1;
            }
            if (c[x] - c_copy[x] > PRECISION) {
                err += 1;
            }
        }
    }

    return err;
}