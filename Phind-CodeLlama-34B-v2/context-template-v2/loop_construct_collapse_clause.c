#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct collapse clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 100;
    const int M = 100;
    double a[N][M];
    double b[N][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = 1.0;
            b[i][j] = 2.0;
        }
    }

    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = a[i][j] + b[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (a[i][j] != 3.0) {
                err = 1;
                break;
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