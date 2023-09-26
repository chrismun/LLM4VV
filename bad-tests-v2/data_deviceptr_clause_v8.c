#ifndef T1
//T1:data,data-region,deviceptr,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    real_t * dev_a = (real_t *)acc_malloc(n * sizeof(real_t));
    real_t * dev_b = (real_t *)acc_malloc(n * sizeof(real_t));

    #pragma acc data copyin(a[0:n]) copyout(b[0:n]) create(dev_a[0:n]) create(dev_b[0:n])
    {
        #pragma acc parallel loop present(a[0:n]) deviceptr(dev_a[0:n], dev_b[0:n])
        for (int x = 0; x < n; ++x){
            dev_a[x] = a[x];
        }

        #pragma acc parallel loop present(dev_a[0:n]) deviceptr(b[0:n], dev_b[0:n])
        for (int x = 0; x < n; ++x){
            b[x] = dev_a[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    acc_free(dev_a);
    acc_free(dev_b);
    free(a);
    free(b);

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