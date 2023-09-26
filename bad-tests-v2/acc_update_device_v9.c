#ifndef T1
//T1:update,construct-independent,V:3.0-3.1
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a;
    int dev_a_present = 0;
    real_t * dev_b;
    int dev_b_present = 0;
    real_t * dev_c;
    int dev_c_present = 0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n])

    #pragma acc parallel copyin(a[0:n], b[0:n]) present(c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }

    #pragma acc update device(c[0:n])

    #pragma acc parallel copyin(a[0:n], c[0:n]) present(b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            b[x] = a[x] + c[x];
        }
    }

    #pragma acc update self(b[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (2 * a[x] + c[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    #pragma acc parallel copyin(c[0:n]) present(a[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = c[x];
        }
    }

    #pragma acc update self(a[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:update,construct-independent,V:4.0-4.0
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a;
    int dev_a_present = 0;
    real_t * dev_b;
    int dev_b_present = 0;
    real_t * dev_c;
    int dev_c_present = 0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n])

    #pragma acc parallel copyin(a[0:n], b[0:n]) present(c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }
    #pragma acc update device_async(c[0:n])

    #pragma acc parallel copyin(a[0:n], c[0:n]) present(b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            b[x] = a[x] + c[x];
        }
    }
    #pragma acc update self_async(b[0:n])

    #pragma acc parallel copyin(c[0:n]) present(a[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = c[x];
        }
    }
    #pragma acc update self_async(a[0:n])

    #pragma acc wait

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (2 * a[x] + c[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    #pragma acc parallel copyin(c[0:n]) present(a[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = c[x];
        }
    }

    #pragma acc wait

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:update,construct-independent,hostonly,V:4.0-4.0
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a;
    int dev_a_present = 0;
    real_t * dev_b;
    int dev_b_present = 0;
    real_t * dev_c;
    int dev_c_present = 0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n])

    #pragma acc kernels
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    #pragma acc exit data delete(a[0:n], b[0:n])

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