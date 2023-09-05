#ifndef T1
// T1: routine copyin create
int test1(){
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 0; i < n; i++){
        a[i] = rand() / (real_t)(RAND_MAX / 10);
        b[i] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n])
    acc_copyin(a, n * sizeof(real_t));
    #pragma acc enter data create(b[0:n])

    #pragma acc kernels
    for (int i = 0; i < n; i++){
        b[i] = a[i];
    }

    #pragma acc exit data delete(a) copyout(b[0:n])

    int err = 0;
    for (int i = 0; i < n; i++){
        if (fabs(b[i] - a[i]) > PRECISION){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; i++){
        failed += test1();
    }
    if (failed > 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}