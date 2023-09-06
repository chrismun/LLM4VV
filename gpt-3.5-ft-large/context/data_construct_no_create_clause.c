#ifndef T1
//T1: data, data, construct, no-reduction, vector, independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t * g = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = rand() / (real_t)(RAND_MAX / 10);
        f[x] = 0.0;
        g[x] = 0.0;
    }

    #pragma acc data create(c[0:n], f[0:n], g[0:n])
    {
        #pragma acc data copyin(a[0:n], b[0:n], d[0:n], e[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop independent
                for (int x = 0; x < n; ++x){
                    c[x] = a[x] + b[x];
                }
                #pragma acc loop independent
                for (int x = 0; x < n; ++x){
                    f[x] = d[x] + e[x];
                }
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop independent
            for (int x = 0; x < n; ++x){
                g[x] = c[x] + f[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(g[x] - (a[x] + b[x] + d[x] + e[x])) > PRECISION){
            err + 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2: define, V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t * g = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = rand() / (real_t)(RAND_MAX / 10);
        f[x] = 0.0;
        g[x] = 0.0;
    }
    #pragma acc data create(c[:n], f[:n], g[:n])
    {
        #pragma acc data copyin(a[:n], b[:n], d[:n], e[:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop independent
                for (int x = 0; x < n; ++x){
                    c[x] = a[x] + b[x];
                }
                #pragma acc loop independent
                for (int x = 0; x < n; ++x){
                    f[x] = d[x] + e[x];
                }
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop independent
            for (int x = 0; x < n; ++x){
                g[x] = c[x] + f[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(g[x] - (a[x] + b[x] + d[x] + e[x]))) {
            err + 1;
            break
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