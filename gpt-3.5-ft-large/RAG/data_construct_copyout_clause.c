#ifndef T1
//T1: data,data-region,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        a_copy[x] = a[x];
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc data copyout(a[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = 0;
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - a_copy[x]) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2: data,data-region,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    int *devtest = (int *)malloc(sizeof(int));

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    #pragma acc data copy(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = rand() / (real_t)(RAND_MAX / 10);
                a_copy[x] = a[x];
                b[x] = 0.0;
            }
        }
    }
    for (int x = 0; x < n; ++x){
        a[x] = -1;
    }
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - a_copy[x]) > PRECISION){
            err += 1;
        }
    }
    #pragma acc data copy(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a_copy[x]) > PRECISION){
            err += 1;
        }
    }
    return err;
}
#endif

#ifndef T3
//T3: data,data-region,construct-independent,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    #pragma acc enter data create(a[0:n], b[0:n])
    if (acc_device_num + 1 > acc_get_num_devices()) {
        for (int x = 0; x < n; ++x) {
            a[x] = rand() / (real_t)(RAND_MAX / 10);
            a_copy[x] = a[x];
            b[x] = 0.0;
        }
        #pragma acc update device(a[0:n], b[0:n])
    }
    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = a[x];
            }
        }
    }
    #pragma acc exit data delete(b[0:n]) copyout(a[0:n])
    for (int x = 0; x < n; ++x) {
        if (fabs(a[x] - a_copy[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4: data,data-region,construct-independent,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        a_copy[x] = a[x];
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc data copy(a[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x) {
                    a[x] = 0;
                }
            }
            #pragma acc exit data copyout(a[0:n])
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(a[x] - a_copy[x])) {
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