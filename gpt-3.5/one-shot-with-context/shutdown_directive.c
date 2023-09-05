#ifndef T1
//T1:shutdown,data,host-data,V:2.5
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    // Perform computation on accelerator device
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            b[x] = a[x] * a[x];
        }
    }

    // Shutdown accelerator device
    #pragma acc shutdown

    // Perform computation on host
    for (int x = 0; x < n; ++x){
        b[x] += a[x] * a[x];
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] * a[x] - b[x]) > PRECISION){
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