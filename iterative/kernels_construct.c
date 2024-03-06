#include "acc_testsuite.h"

#define N 100

int test1(){
    int err = 0;
    int i, j;
    int a[N][N];
    int b[N][N];

    // Initialize the arrays
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = rand() % 100;
            b[i][j] = 0;
        }
    }

    // Perform operation on the arrays using kernels construct
    #pragma acc kernels copyin(a[0:N][0:N]) copyout(b[0:N][0:N])
    {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                b[i][j] = a[i][j] * 2;
            }
        }
    }

    // Check the results
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (b[i][j] != a[i][j] * 2) {
                err++;
            }
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    srand(SEED);
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}