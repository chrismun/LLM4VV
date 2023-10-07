#ifndef T1
//T1:present,data,data-region,V:3.0-3.2
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    read_data(a, b);

    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc data present(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * a[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x] - b[x];
            }

        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n])
    bools = (real_t*)malloc(n * sizeof(real_t));
    for (int x = 0; x < n; ++x){
        bools[x] = 1;
    }

    for (int x = 0; x < n; ++x){
        if (fabs(1 - a[x]/(b[x] + 2)) > PRECISION){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:present,data,data-region,V:3.0-3.2
int test2(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = 0;
        d[x] = 0;
        e[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n], d[0:n], e[0:n])
    #pragma acc data present(a[0:n], b[0:n], c[0:n], d[0:n], e[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = 1;
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = 2;
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = 3;
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = a[x] + c[x];
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] + d[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                e[x] = a[x] + b[x];
            }
        }
    }
    #pragma acc exit data copyout(a[0:n], b[0:n], c[0:n], d[0:n], e[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (3 + a[x]/2 + a[x]/3)) > PRECISION * 2){
            err += 1;
        }
        if (fabs(b[x] - 2) > PRECISION){
            err += 1;
        }
        if (fabs(c[x] - 3) > PRECISION){
            err += 1;
        }
        if (fabs(d[x] - (1 + c[x])) > PRECISION){
            err += 1;
        }
        if (fabs(e[x] - (a[x] + b[x])) > PRECISION * 2){
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
    return failcode;
}