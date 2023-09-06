#ifndef T1
//T1: host_data, data, host (no sane way to check)
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    int * devtest = (int *)malloc(sizeof(int));
    host_data_begin(devtest)
        *devtest = 1;
    host_data_end(devtest)

    if (devtest[0] == 0){
        free(devtest);
        for (int x = 0; x < n; ++x){
            a[x] = (real_t) rand() / (real_t)(RAND_MAX / 10);
            b[x] = (real_t) rand() / (real_t)(RAND_MAX / 10);
            c[x] = 0.0;
        }

        #pragma acc data copyin(a[0:n], b[0:n]) copy(c[0:n])
        {
            #pragma acc host_data use_device(c[0:n])
            {
                #pragma acc parallel
                {
                    #pragma acc loop
                    for (int x = 0; x < n; ++x){
                        c[x] = a[x] + b[x];
                    }
                }
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