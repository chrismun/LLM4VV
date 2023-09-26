#ifndef T2
//T2:detach,data,runtime,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 1; x < n-1; ++x){
                b[x] = (a[x-1] + a[x] + a[x+1]) / 3.0;
            }
        }

        #pragma acc parallel loop vector_length(128) num_workers(32) device_type(nvidia) detach(b)
        for (int x = 0; x < n; ++x){
            a[x] = b[x];
        }
    }

    for (int x = 1; x < n-1; ++x){
        if (fabs(b[x] - (a[x-1] + a[x] + a[x+1]) / 3.0) > PRECISION){
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