#ifndef T1
//T1:memcpy:d2d
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 0; i < n; ++i){
        a[i] = rand() / (real_t)(RAND_MAX / 10);
        b[i] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n])

    #pragma acc parallel present(a[0:n]) async
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i){
            b[i] = a[i];
        }
    }

    #pragma acc wait

    for (int i = 0; i < n; ++i){
        if (fabs(a[i] - b[i]) > PRECISION){
            err += 1;
            break;
        }
    }

    #pragma acc exit data delete(a[0:n])

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
 
    #ifndef T1
    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    #endif

    return failcode;
}