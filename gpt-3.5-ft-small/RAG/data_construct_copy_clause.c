#ifndef T1
//T1:data,data-region,defaultnone,V:2.0-2.7
int test1(){
    int err = 0;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(10 * n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));
    int *d = (int *)malloc((n/10 + 1) * 10 * sizeof(int));
    real_t false_margin = pow(exp(1), log(.5)/n);

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        c[x] = 0;
    }
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            b[x * n + y] = 1;
        }
    }
    for (int x = 0; x < (n/10 + 1) * 10; ++x){
        d[x] = 0;
    }

    acc_copyin(a, n * sizeof(int));
    #pragma acc data copy(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = 2;
            }
        }
    }
    #pragma acc data copyin(a[0:n]) copy(b[0:10 * n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            //#pragma acc data create(c[0:n]) copy(c[0:n])
            for (int x = 0; x < 10 * n; ++x){
                b[x] = b[x] + a[(x % n)] + c[(x % n)] + d[x];
            }
        }
    }
    #pragma acc data copyout(b[0:10 * n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10 * n; ++x){
                b[x] = b[x] + 2;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            if (fabs(b[x * n + y] - (5 + false_margin)) > false_margin){
                err += 1;
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
    for (int x = 1; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}