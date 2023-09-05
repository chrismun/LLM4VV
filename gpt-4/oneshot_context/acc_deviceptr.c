int test_deviceptr() {
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_a;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    
    #pragma acc data create(a[0:n])
    {
        dev_a = acc_deviceptr(a);
    }

    if (dev_a == NULL){
        err += 1;
    }
    free(a);
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_deviceptr();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}