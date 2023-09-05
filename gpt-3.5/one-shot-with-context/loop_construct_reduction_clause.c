#ifndef T1
//T1:parallel,data,data-region,V:2.7-3.1
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t sum = 0.0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n]) copy(sum)
    {
        #pragma acc parallel loop reduction(+:sum)
        for (int x = 0; x < n; ++x){
            sum += a[x];
        }
    }

    real_t expected_sum = 0.0;
    for (int x = 0; x < n; ++x){
        expected_sum += a[x];
    }

    if (fabs(sum - expected_sum) > PRECISION){
        err += 1;
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