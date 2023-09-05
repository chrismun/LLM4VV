#ifndef T2
//T2:construct,compute,async,V:2.0-2.5
int test2(){
    int err = 0;

    srand(SEED);
    real_t *a = (real_t *)malloc(N * sizeof(real_t));
    real_t *b = (real_t *)malloc(N * sizeof(real_t));
    real_t *c = (real_t *)malloc(N * sizeof(real_t));
    real_t *d = (real_t *)malloc(N * sizeof(real_t));

    for (int x = 0; x < N; ++x){
        a[x] = 1.0;
        b[x] = 2.0;
        c[x] = 0.0;
        d[x] = 0.0;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N]) create(d[0:N])
    {
        #pragma acc parallel
        {
            #pragma acc loop independent async(1)
            for (int x = 0; x < N; ++x){
                d[x] = a[x] + b[x];
            }

            #pragma acc loop independent async(2)
            for (int x = 0; x < N; ++x){
                c[x] = d[x] * b[x];
            }
        }
    }

    // Explicitly waiting for completion of async(2)
    #pragma acc wait(2)

    for (int x = 0; x < N; ++x){
        real_t computed_result = (a[x] + b[x]) * b[x];
        if (fabs(computed_result - c[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}