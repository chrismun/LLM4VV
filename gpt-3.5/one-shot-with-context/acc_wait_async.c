int test_acc_wait_async(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }

        int async1 = acc_async_test();
        #pragma acc wait async(async1)

        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] += 1.0;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (a[x] + 1.0)) > PRECISION){
            err += 1;
            break;
        }
    }

    free(a);
    free(b);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    failed = failed + test_acc_wait_async();

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}