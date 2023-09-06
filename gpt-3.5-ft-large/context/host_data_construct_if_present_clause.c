#ifndef T1
//T1:present,data,data-region,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:n]) create(present: e[0:n])
    #pragma acc host_data use_device(present, c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }
    #pragma acc data copyin(c[0:n], d[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            e[x] = c[x] + d[x];
        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n], c[0:n], d[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(e[x] - (a[x] + b[x] + d[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:present,data,data-region,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    int * devtest = (int *)malloc(sizeof(int));
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    devtest[0] = 1;
    #pragma acc data copyin(devtest[0:1])
    #pragma acc parallel
    {
        devtest[0] = 0;
    }

    if (devtest[0] == 1){
        for (int x = 0; x < n; ++x){
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            b[x] = rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0;
        }

        #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:n])
        #pragma acc host_data if_present(c, a[0:n], b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] * b[x];
            }
        }
        #pragma acc enter data copyin(c[0:n]) 
        #pragma acc host_data if_present(a[0:n], b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += a[x] + b[x];
            }
        }
        #pragma acc exit data delete(a[0:n], b[0:n], c[0:n])

        for (int x = 0; x < n; ++x){
            if (fabs(c[x] - (a[x] + b[x]))) {
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
    return failcode;
}