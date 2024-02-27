#include "acc_testsuite.h"
#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * c = (int *)malloc(n * sizeof(int));
    real_t ** d = (real_t**)malloc(n * sizeof(real_t *));
    real_t ** e = (real_t**)malloc(n * sizeof(real_t *));
    real_t ** f = (real_t**)malloc(n * sizeof(real_t *));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 1;
        c[x] = 0;
        d[x] = (real_t *)malloc(n * sizeof(real_t));
        e[x] = (real_t *)malloc(n * sizeof(real_t));
        f[x] = (real_t *)malloc(n * sizeof(real_t));
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            d[x][y] = rand() / (real_t)(RAND_MAX / 10);
            e[x][y] = rand() / (real_t)(RAND_MAX / 10);
            f[x][y] = 0.0;
        }
    }

    #pragma acc data copyin(d[0:n][0:n], e[0:n][0:n]) copyout(f[0:n][0:n]) present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                c[x] += d[x][y] + e[x][y];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > 3*n*PRECISION){
            err += 1;
            break;
        }
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            if (fabs(f[x][y] - (d[x][y] + e[x][y])) > 4 * PRECISION){
                err += 1;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            f[x][y] = 4;
        }
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            d[x][y] = a[x] * b[x];
            e[x][y] = a[x] * b[x];
        }
    }
    #pragma acc data copyin(d[0:n][0:n], e[0:n][0:n]) copyout(f[0:n][0:n]) present(a[0:n], b[0:n])
    {

        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                f[x][y] += d[x][y] + e[x][y];
            }
        }

    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            if (fabs(f[x][y] - 4) > PRECISION){
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