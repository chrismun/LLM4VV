#ifndef T1
//T1:loop,tile,combined-constructs,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    int32_t * b = (int32_t *)malloc(10 * sizeof(int32_t));
    real_t * exp = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * dev_a = (real_t *)malloc(10 * n * sizeof(real_t));
    int32_t * dev_b = (int32_t *)malloc(10 * sizeof(int32_t));

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            a[x * n + y] = rand() / (real_t)(RAND_MAX / 10);
        }
        for (int y = 0; y < 10; ++y){
            b[y] = rand() % n;
        }
    }

    #pragma acc enter data copyin(a[0:10*n], b[0:10], dev_a[0:10*n], dev_b[0:10])
    #pragma acc kernels loop gang worker tile(32) independent
    for (int x = 0; x < 10; ++x){
        #pragma acc loop gang worker tile(32) independent
        for (int y = 0; y < 10; ++y){
            #pragma acc loop gang worker vector independent
            for (int z = 0; z < n; ++z){
                dev_a[x * n + z] += (dev_a[x * n + z] + a[x * n + z]) * a[x * n + z];
                if (b[x] == z){
                    dev_a[x * n + z] += dev_a[x * n + z] * a[x * n + z];
                }
            }
            dev_b[y] = (int32_t)(dev_a[x * n + y] + 1);
            dev_a[x * n + y] = 0;
        }
    }
    #pragma acc exit data copyout(a[0:10*n], b[0:10], dev_a[0:10*n], dev_b[0:10])

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            exp[x * n + y] = a[x * n + y];
            a[x * n + y] = 0;
        }
        for (int y = 0; y < 10; ++y){
            exp[x * n + b[y]] += dev_b[y] + 1;
        }
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < 10; ++y){
            for (int z = 0; z < n; ++z){
                a[x * n + z] += (exp[x * n + z] + a[x * n + z]) * exp[x * n + z];
                if (b[x] == z){
                    a[x * n + z] += a[x * n + z] * exp[x * n + z];
                }
            }
            if (fabs(a[x * n + y] - dev_a[x * n + y]) > PRECISION) {
                err = 1;
            }
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