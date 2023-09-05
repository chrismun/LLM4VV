#ifndef T1
//T1:parallel,data,data-region,atomic,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int sum = 0;
    int *a = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % 10;
    }

    #pragma acc data copyin(a[0:n]) copy(sum)
    {
        #pragma acc parallel
        {
            int private_sum = 0;

            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc atomic
                private_sum += a[x];
            }

            #pragma acc atomic
            sum += private_sum;
        }
    }

    int expected_sum = 0;
    for (int x = 0; x < n; ++x){
        expected_sum += a[x];
    }

    if (sum != expected_sum){
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