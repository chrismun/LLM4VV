#ifndef T1
//T1:loop,private,V:2.7-3.0
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * a_copy = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 3 * PREC_MOD;
        a_copy[x] = a[x];
        b[x] = rand() / (real_t)(RAND_MAX / 10) * PREC_MOD;
    }

    #pragma acc data copyin(b[0:10*n]) copyout(c[0:n]) copy(a[0:10*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang private(c)
            for (int x = 0; x < 10; ++x){
                for (int y = 0; y < n; ++y){
                    c[y] = 0.0;
                }
                #pragma acc loop worker reduction(+:c)
                for (int y = 0; y < n; ++y){
                    c[y] = c[y] + b[x * n + y];
                }
                #pragma acc loop vector
                for (int y = 0; y < n; ++y){
                    a[x * n + y] += c[y]/2;
                }
            }
        }
    }

    for (int x = 0; x < 10 * n; ++x){
        if (fabs(a[x] - (4 * PREC_MOD)) > PREC){
            err += 1;
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