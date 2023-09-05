#ifndef T1
//T1:devptr,data,construct-V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(a[0:n])

    real_t *dev_ptr = (real_t *)acc_deviceptr(a);
    real_t *host_ptr = (real_t *)acc_hostptr(dev_ptr);

    if (host_ptr != a){
        err += 1;
    }

    #pragma acc exit data delete(a[0:n])

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