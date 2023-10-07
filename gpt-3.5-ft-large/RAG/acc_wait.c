#ifndef T1
//T1:runtime,async,construct-independent,wait,V:2.0-2.7
int test1(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
    }

    #pragma acc data copy(a[0:n])
    {
        #pragma acc wait
        {
            #pragma acc parallel async(1)
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = a[x] + 1;
                }
            }
        }
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] + 1;
            }
        }
        #pragma acc wait
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] + 2)) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,async,construct-independent,wait,V:2.0-2.7
int test2(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    int async_id;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
    }

    #pragma acc data copy(a[0:n])
    {
        init_vector(a, 1);
        #pragma acc wait
        {
            init_vector(a, 3);
            #pragma acc parallel loop async(1) worker(0)
            for (int x = 0; x < n; ++x){
                a[x] = a[x] + 1;
            }
        }
        init_vector(a, 2);
        #pragma acc wait
        #pragma acc parallel loop async(2) worker(0)
        for (int x = 0; x < n; ++x){
            a[x] = a[x] + 1;
        }
        #pragma acc wait
        init_vector(a, 5);
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (3 + b[x])) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

int init_test(){
    int err = 0;
    int is_host = 1;

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
    }

    #pragma acc data copy(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = 0;
            }
        }
        #pragma acc wait
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x]) > PRECISION){
            err += 1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION) {
            is_host = 0;
        }
    }
    if (is_host){
        return 1;
    }
    else {
        return err;
    }
}

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
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + init_test();
    }
    if (failed != 0){
        failcode = failcode + (1 << 13);
    }
    return failcode;
}