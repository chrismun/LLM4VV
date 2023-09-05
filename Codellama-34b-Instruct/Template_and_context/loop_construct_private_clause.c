#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int n = 10;
    int a[n][n];
    int b[n][n];
    int c[n][n];
    int tmp[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
            b[i][j] = 0;
            c[i][j] = 0;
            tmp[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                tmp[i][j] = b[j][k] + c[j][k];
                a[i][j] = a[i][j] + tmp[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (a[i][j] != b[j][k] + c[j][k]) {
                    err = 1;
                    break;
                }
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