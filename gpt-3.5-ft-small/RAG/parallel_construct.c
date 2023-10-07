#ifndef T1
//T1:parallel,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t sum = 0.0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        sum += a[x];
    }

#pragma acc data copy(a[0:n])
{
#pragma acc parallel
    {
        real_t private_sum = 0.0;
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            private_sum += a[x];
        }
        #pragma acc atomic
            sum += private_sum;
    }
}

    return compare_real(sum, n * (sum / n));
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + !(test1());
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}