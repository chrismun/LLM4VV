#ifndef T1
//T1:parallel,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;

    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = x + 1;
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) copy(b[0:n])
    {
        #pragma acc parallel loop independent
        for (int x = 0; x < n; ++x){
            b[x] = 2 * a[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] != 2 * a[x]){
            err += 1;
            break;
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