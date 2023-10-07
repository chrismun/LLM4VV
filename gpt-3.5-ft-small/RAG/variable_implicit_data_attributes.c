#ifndef T1
//T1:runtime,data,data-region,construct-independent,V:2.5-2.7
int test1(){
    int errcode = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * c_copy = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        c_copy[x] = 0;
    }

    acc_enter_data_copyin(a, n * sizeof(real_t));
    acc_enter_data_copyin(b, n * sizeof(real_t));
    acc_enter_data_create(c, n * sizeof(real_t));

    #pragma acc parallel
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < n; ++x){
        c_copy[x] = a[x] + b[x];
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c_copy[x] - c[x]) > PRECISION){
            errcode = 1;
        }
    }

    return errcode;
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