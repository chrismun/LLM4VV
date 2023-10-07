#ifndef T1
//T1:declare,data,dx11,runtime,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;

    real_t * restrict a;
    real_t * restrict b;
    real_t * restrict c;

    a = (real_t *)malloc(n * sizeof(real_t));
    b = (real_t *)malloc(n * sizeof(real_t));
    c = (real_t *)malloc(2 * n * sizeof(real_t));

    real_t *d = (real_t *) acc_malloc((2 * n) * sizeof(real_t));
    real_t * deal_a = (real_t *) acc_malloc(n * sizeof(real_t));
    real_t * deal_b = (real_t *) acc_malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        deal_a[x] = a[x] = rand() / (real_t)(RAND_MAX/10);
        deal_b[x] = b[x] = rand() / (real_t)(RAND_MAX/10);
    }
    for (int x = 0; x < 2*n; ++x){
        d[x] = rand() / (real_t)(RAND_MAX/10);
    }

    #pragma acc data deviceptr(deal_a, deal_b, d)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                deal_a[x] = 0;
                deal_b[x] = 0;
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc loop vector
                for (int y = 0; y < 2; ++y){
                    deal_a[x] = deal_a[x] + d[x * 2 + y] * deal_b[x];
            }   }
        }
    }

    for (int x = 0; x < n; ++x){
        c[x] = 0;
        for (int y = 0; y < n; ++y){
            c[x] = c[x] + a[y] * b[y];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - deal_a[x]) > PRECISION){
            err = 1;
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