#ifndef T1
//T1:loop,construct-independent,V:2.6-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t multiplyer = 1;

    for (int x = 0; x < n; ++ x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel seq
        {
            #pragma acc loop seq
            for (int x = 0; x < n; ++x){
                c[x] = (a[x] + b[x]);
            }
            multiplyer = 1;
            #pragma acc loop seq
            for (int x = 0; x < n; ++x){
                c[x] *= (a[x] + b[x]) + multiplyer;
            multiplyer += 1;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (2 * (a[x] + b[x])))) > PRECISION * (a[x] + b[x])){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:loop,construct-independent,reference-counting,V:2.6-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b_copy = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * c_copy = (real_t *)malloc(10 * n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n])
    {
        for (int x = 0; x < 10 * n; ++x){
            a_copy[x] = a[x];
            b_copy[x] = b[x];
        }
        #pragma acc parallel seq
        {
            #pragma acc loop seq
            for (int x = 0; x < 10 * n; ++x){
                a[x] = 0;
                b[x] = 0;
            }
        }
        for (int x = 0; x < 10 * n; ++x){
            if (fabs(a[x]) > PRECISION) {
                devtest[0] = 1;
            }
            if (fabs(b[x]) > PRECISION) {
                devtest[0] = 1;
            }
        }
    }

    for (int x = 0; x < 10 * n; ++x){
        if (fabs(devtest[0]) > PRECISION){
            err += 1;
        }
        if (fabs(a[x] - a_copy[x]) > PRECISION) {
            err += 1;
        }
        if (fabs(b[x] - b_copy[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:loop,construct-independent,V:2.6-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
    devtest[0] = 0;

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = 0;
    }

    #pragma acc data copyout(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop seq
            for (int x = 0; x < n; ++x) {
                a[x] = 1;
            }
            #pragma acc loop seq
            for (int x = 0; x < n; ++x){
                b[x] = 1;
            }
            #pragma acc loop seq
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 2) > PRECISION) {
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
    return failcode;
}