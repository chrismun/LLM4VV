#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define N 1000
#define SEED 123
#define PRECISION 0.0001
#define NUM_TEST_CALLS 1

int test_collapse_clause(){
    int err = 0;
    srand(SEED);
    double *a = (double *)malloc(N * sizeof(double));
    double *b = (double *)malloc(N * sizeof(double));

    for (int x = 0; x < N; ++x){
        a[x] = rand() / (double)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc kernels loop collapse(2)
        for (int i = 0; i < 10; ++i){
            for (int j = 0; j < 10; ++j){
                b[i * 10 + j] = a[i * 10 + j];
            }
        }
    }

    for (int x = 0; x < N; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_collapse_clause();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}