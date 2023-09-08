#ifndef T1
//T1:host_data,data_region,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t c = 0;

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc data copyout(a[0:n]) present(b[0:n])
    {
        #pragma acc host_data use_device(a[0:n]) if(c > 0)
        {
            for (int x = 0; x < n; ++x){
                a[x] += b[x];
            }
        }
        c = 1;
        #pragma acc host_data use_device(a[0:n]) if(c > 0)
        {
            for (int x = 0; x < n; ++x){
                a[x] += b[x];
            }
        }
    }
    #pragma acc exit data delete(b[0:n])
    for (int x = 0; x < n; ++x){
        a[x] -= b[x];
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x]) > PRECISION){
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