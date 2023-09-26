#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 1;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = rand() / (real_t)(RAND_MAX / 10);
        f[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n], d[0:n], e[0:n]) create(c[0:n]) copyout(f[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = c[x] + c[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = c[x] + a[x] + b[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = c[x] + d[x] + e[x];
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                f[x] = c[x] * c[x];
            }
        }
        #pragma acc update device(c[0:n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = c[x] + c[x];
            }
        }
        #pragma acc update host(c[0:n])
        #pragma acc exit data copyout(f[0:n]) delete(a[0:n], b[0:n], d[0:n], e[0:n])

    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (1 + a[x] + b[x] + d[x] + e[x]))) {
            err += 1;
        }
        if (fabs(f[x] - ((1 + a[x] + b[x] + d[x] + e[x])) * ((1 + a[x] + b[x] + d[x] + e[x])))) > 4 * PRECISION) {
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
    return failcode;
}