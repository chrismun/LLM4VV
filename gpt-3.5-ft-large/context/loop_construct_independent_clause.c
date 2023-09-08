#ifndef T1
//T1:loop,independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t avg = 0.0;

    for (int x = 0; x < 10 * n; ++x){
        a[x] = (999.0 / RAND_MAX) * rand();
        b[x] = (999.0 / RAND_MAX) * rand();
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copyout(c[0:10*n])
    {
        #pragma acc parallel
        {
	    #pragma acc loop independent
            for (int x = 0; x < 10; ++x){
                avg = 0;
                #pragma acc loop independent reduction(+:avg)
                for (int y = 0; y < n; ++y){
                    avg += a[x * n + y] / n;
                }
                #pragma acc loop independent
                for (int y = 0; y < n; ++y){
                    c[x * n + y] = (a[x * n + y] - avg) * b[x * n + y];
                }
            }
        }
    }

    real_t avgn;
    for (int x = 0; x < 10; ++x){
        avgn = 0;
        for (int y = 0; y < n; ++y){
            avgn += a[x * n + y] / n;
        }
        for (int y = 0; y < n; ++y){
            if (fabs(c[x * n + y] - ((a[x * n + y] - avgn) * b[x * n + y])) > 30 * PRECISION){
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}