#ifndef T1
//T1:construct-independent-loop-interchange,collapse,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < n; ++x){
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copy(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop collapse(2)
            for (int x = 0; x < 10; ++x){
                for (int y = 0; y < n; ++y){
                    c[y] += a[x * n + y] + b[x * n + y];
                }
            }
        }
    }

    real_t temp = 0;
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            temp = a[x * n + y] + b[x * n + y];
            if (fabs(c[y] - temp) > PRECISION * 2){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:construct-independent-update,collapse,devonly,V:2.7-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(10 * n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(a[0:10*n])
    #pragma acc enter data copyin(a[0:10*n])
    for (int x = 0; x < 10 * n; ++x){
        a_copy[x] = a[x];
    }
    #pragma acc data copyin(a[0:10*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop collapse(2)
            for (int x = 0; x < 10; ++x){
                for (int y = 0; y < n y++){
                    a[x * n + y] += a[x * n + y];
                }
            }
        }
    }

    for (int x = 0; x < 10 * n; ++x){
        if (fabs(a[x] - (a_copy[x] + a_copy[x]))) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:construct-independent-loop-interchange,collapse,devonly,V:2.7-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < n; ++x){
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copy(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop collapse(2)
            for (int x = 0; x < 10; ++x){
                for (int y = 0; y < n; ++y){
                    c[y] += a[x * n + y] + b[x * n + y];
                }
            }
        }
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copy(c[0:n])
    {
        #pragma acc parallel
        {
            for (int x = 0; x < n; ++x){
                for (int y = 0; y < 10; ++y){
                    c[x] += a[x + y * n] + b[x + y * n];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x] + a[x + n] + b[x + n] + a[x + 2 * n] + b[x + 2 * n] + a[x + 3 * n] + b[x + 3 * n] + a[x + 4 * n] + b[x + 4 * n] + a[x + 5 * n] + b[x + 5 * n] + a[x + 6 * n] + b[x + 6 * n] + a[x + 7 * n] + b[x + 7 * n] + a[x + 8 * n] + b[x + 8 * n] + a[x + 9 * n] + b[x + 9 * n]))) > 2 * PRECISION{
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