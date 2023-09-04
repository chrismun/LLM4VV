#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int m = 100;
    int k = 100;
    int i, j, k;
    int a[n][m][k];
    int b[n][m][k];
    int c[n][m][k];

    #pragma acc parallel loop collapse(2)
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            for (k = 0; k < k; k++) {
                a[i][j][k] = i + j + k;
                b[i][j][k] = i + j + k;
                c[i][j][k] = i + j + k;
            }
        }
    }

    #pragma acc parallel loop collapse(2)
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            for (k = 0; k < k; k++) {
                a[i][j][k] += b[i][j][k] + c[i][j][k];
            }
        }
    }

    #pragma acc parallel loop collapse(2)
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            for (k = 0; k < k; k++) {
                a[i][j][k] += b[i][j][k] + c[i][j][k];
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