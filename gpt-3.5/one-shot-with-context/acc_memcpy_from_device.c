#ifndef T2
//T2:memcpy,async,devonly,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    real_t * a_copy = (real_t *)acc_malloc(n * sizeof(real_t));
    real_t * b_copy = (real_t *)acc_malloc(n * sizeof(real_t));
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel 
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = rand() / (real_t)(RAND_MAX / 10);
                b[x] = 0.0;
            }
        }
        #pragma acc update device(a[0:n]) async
        #pragma acc parallel 
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a_copy[x] = a[x];
            }
        }
        #pragma acc update host(b[0:n]) async
        #pragma acc parallel 
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b_copy[x] = b[x];
            }
        }
    }

    #pragma acc data copyin(a_copy[0:n])
    {
        #pragma acc parallel 
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a_copy[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
        if (fabs(a_copy[x] - b_copy[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    acc_free(a_copy);
    acc_free(b_copy);
    free(a);
    free(b);

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