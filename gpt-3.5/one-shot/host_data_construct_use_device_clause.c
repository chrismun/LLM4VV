#ifndef T1
//T1:parallel,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 0; i < n; ++i){
        a[i] = rand() / (real_t)(RAND_MAX / 10);
        b[i] = rand() / (real_t)(RAND_MAX / 10);
        c[i] = 0.0;
        d[i] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:n]) use_device(d[0:n])

    #pragma acc parallel num_gangs(1) copyin(a[0:n], b[0:n]) use_device(d[0:n]) present(c[0:n])
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i){
            c[i] = a[i] + b[i];
            d[i] = c[i];
        }
    }

    #pragma acc exit data copyout(c[0:n]) delete(a[0:n], b[0:n]) use_host(d[0:n])

    for (int i = 0; i < n; ++i){
        if (fabs(c[i] - d[i]) > PRECISION){
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
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}