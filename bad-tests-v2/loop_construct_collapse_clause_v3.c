#ifndef T1
//T1:parallel,data,data-region,loop,collapse,V:2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(m * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(m * n * sizeof(real_t));

    for (int x = 0; x < m * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:m*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop collapse(2)
            for (int i = 0; i < m; ++i){
                for (int j = 0; j < n; ++j){
                    b[i * n + j] = a[i * n + j];
                }
            }
        }
    }

    for (int x = 0; x < m * n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
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