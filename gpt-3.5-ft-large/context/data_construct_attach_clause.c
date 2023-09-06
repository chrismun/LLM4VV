#ifndef T1
//T1:data,data-region,construct-independent,attach,detach,V:3.0-3.2
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }
    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc data copyout(c[0:n]) attach(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }
    #pragma acc exit data copyout(a[0:n], b[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:data,data-region,enter-data,attach,detach,reference-counting,V:3.0-3.2
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(real_t));

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
            c[x] = 1;
        }
        #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n])
        for (int x = 0; x < n; ++x){
            c[x] = 2.0;
            #pragma acc data copy(c[0:n]) attach(a[0:n], b[0:n])
            {
                #pragma acc parallel
                {
                    #pragma acc loop
                    for (int y = 0; y < n; ++y) {
                        c[x] += a[y] + b[y];
                    }
                }
            }
        }

        for (int x = 0; x < n; ++x) {
            if (fabs(c[x] - (2 + a[x] + b[x])) > PRECISION) {
                err += 1;
            }
        }

        #pragma acc exit data copyout(a[0:n], b[0:n], c[0:n])
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
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