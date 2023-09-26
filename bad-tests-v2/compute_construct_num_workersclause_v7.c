#ifndef T1
//T1:parallel,loop,num_workers,V:2.5-2.11
int test1(){
    int err = 0;
    int limit = n + 1;
    int default_workers = 0;
    real_t  * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (1.0 * RAND_MAX);
    }
    #pragma acc data copyin(a[0:n]) create(b[0:n])
    {
        #pragma acc kernels num_workers(default_workers)
        {
            #pragma acc loop
            for (int x = 0; x < limit; ++x){
                b[x] = 1;
            }
        }

        default_workers = acc_get_num_workers();
    }
    for (int x = 0; x < n; ++x){
        if(a[x] != b[x]){
            err = 1;
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