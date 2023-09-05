#ifndef T1
//T1:serial,default,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = 0.0;
    }

    #pragma acc data copyout(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = b[x] + 1.0;
            }
        }
        #pragma acc serial
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] += 1.0;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - 2.0) > PRECISION){
            err += 1;
            break;
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