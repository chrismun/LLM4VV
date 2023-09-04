#include "acc_testsuite.h"

int test_data_construct(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = test_data_construct();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}