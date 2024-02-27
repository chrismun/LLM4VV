#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct self clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t **a = (real_t **)malloc(n * sizeof(real_t *));
    real_t *b = new real_t[n];
    real_t *c = (real_t *)malloc(10 * n * sizeof(real_t *));
    std::generate(b, b + n, std::rand);

    for (int x = 0; x < n; ++x){
        a[x] = (real_t *)malloc(10 * sizeof(real_t));
        for (int y = 0; y < 10; ++y){
            a[x][y] = b[x];
        }
    }
    #pragma acc data copyin(a[0:n][0:10]) copyout(c[0:n*10])
    {
        #pragma acc parallel loop self(c)
        for (int x = 0; x < n; ++x){
            for (int y = 0; y < 10; ++y){
                c[x * 10 + y] = a[x][y];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < 10; ++y){
            if (fabs(c[x * 10 + y] - a[x][y]) > PRECISION){
                err += 1;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < 10; ++y){
            if (fabs(c[x * 10 + y] - a[x][y]) > PRECISION){
                err += 1;
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