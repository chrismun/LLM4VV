#ifndef T1
//T1:parallel,loop,combined-constructs,V:2.7-TO-3.0
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int found = 0;
    int temp = 0;

    for (int x = 0; x < n; ++x){
        a[x] = (n % 2) ? rand() / (real_t)(RAND_MAX / 10) : rand() / (real_t)(RAND_MAX / -10);
        b[x] = (n % 2) ? rand() / (real_t)(RAND_MAX / 10) : rand() / (real_t)(RAND_MAX / -10);
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel loop vector_length(16)
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > (2*PRECISION)){
            err += 1;
            break;
        }
    }

    for (int x = 0; x < n; ++x){
        if ((c[x] - (a[x] + b[x]))) {
            temp = temp + n * 10;
        }
    }
    #pragma acc parallel copy(found)
    {
        #pragma acc loop vector
        for (int x = 0; x < n; ++x){
            if (temp == (x * 10)){
                found = 1;
            }
        }
    }

    if (!found){
        err = 1;
    }

    return err;
}
#endif

#ifndef T2
//T2:kernels,if,combined-constructs,devonly,V:2.7-TO-3.1
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc kernels loop vector_length(16)
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:parallel,loop,V:2.7-TO-3.0
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel loop vector_length(16)
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(c[x] - (a[x] + b[x]))) {
            err = 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:parallel,loop,V:2.7-TO-3.0
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
    int * a_cop = (int *)malloc(n * sizeof(int));
    real_t * b_cop = (real_t *)malloc(n * sizeof(real_t));
    real_t * c_cop = (real_t *)malloc(n * sizeof(real_t));

    devtest[0] = 1;
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
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
        #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
        {
            for (int x = 0; x < n; ++x){
                a[x] = 1;
            }
            #pragma acc parallel 
            {
                #pragma acc loop vector_length(32)
                for (int x = 0; x < n; ++x){
                    a[x] = 2;
                }
            }
    
        }
        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - 2) > PRECISION){
                err = 1;
            }
        }
    }
    else {
        err = 1;
    }

    return err;
}
#endif

#ifndef T5
//T5:parallel,loop,V:2.7-TO-3.0
int test5(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * 10 * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * 10 * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * passed = (int *)malloc(sizeof(int));
    int total = 0;

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    for (int x = 0; x < n; ++x){
        c[x] = 0;
    }

    for (int x = 0; x < n; ++x){
        total = 0;
        for (int y = 0; y < 10; ++y){
            total += a[n * y + x] > b[n * y + x] ? a[n * y + x] - b[n * y + x] : b[n * y + x] - a[n * y + x];
        }
        passed[0] = 1;
        #pragma acc data copyin(a[0:10*n], b[0:10*n]) copy(c[0:n])
        {
            #pragma acc parallel loop vector_length(16)
            for (int y = 0; y < 10; ++y){
                #pragma acc loop vector vector_length(16) reduction(+:total)
                for (int x = 0; x < n; ++x){
                    total += a[n * y + x] - b[n * y + x];
                }
            }
            #pragma acc update host(c[0:n])
        }
        for (int y = 0; y < 10; ++y){
            for (int x = 0; x < n; ++x){
                total -= b[n * y + x];
            }
        }
        if (fabs(total) > (10 * n * PRECISION)){
            err++;
            for (int x = 0; x < n; ++x){
                c[n * y + x] = 10;
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
#ifndef T5
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test5();
    }
    if (failed != 0){
        failcode = failcode + (1 << 4);
    }
#endif
    return failcode;
}