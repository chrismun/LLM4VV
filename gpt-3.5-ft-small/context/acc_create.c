#ifndef T1
//T1:runtime,construct-independent,create,loop,default-independent,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(2 * n * sizeof(real_t));
    real_t *hostdata = (real_t *)malloc((n + 20) * sizeof(real_t));
    real_t *devdata = (real_t *)malloc((n + 20) * sizeof(real_t));

    for (int x = 0; x < 20; ++x){
        hostdata[x] = 0;
    }
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        for (int y = 0; y < 2; ++y){
            b[x + y * n] = 0.0;
        }
    }

    #pragma acc data copy(devdata[0:20])
    {
        #pragma acc create(hostdata[0:20]) copyin(a[0:n]) copyout(devdata[0:20])
        {
            for (int x = 0; x < 20; ++x){
                hostdata[x] = 0;
            }
            #pragma acc parallel
            {
                #pragma acc loop independent
                for (int x = 0; x < n; ++x){
                    devdata[x + 20] = a[x] * a[x];
                }
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop independent
            for (int x = 0; x < n; ++x){
                for (int y = 0; y < 2; ++y){
                    b[x + y * n] = devdata[x + y * (n + 20)];
                    devdata[x + y * (n + 20)] = 0.0;
                }
            }
        }
    }

    real_t temp;
    for (int x = 0; x < n; ++x){
        temp = 0;
        for (int y = 0; y < n; ++y){
            temp += a[y] * a[y];
        }
        if (fabs(temp - b[x]) > PRECISION){
            err += 1;
        }
    }
    for (int x = n; x < 2 * n; ++x){
        if (b[x] != 0){
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