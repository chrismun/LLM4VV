#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int n = 100;
    int a[n][n][n], b[n][n], c[n][n];
    int tmp[n][n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            b[i][j] = rand() % 100;
            c[i][j] = rand() % 100;
            for (int k = 0; k < n; ++k) {
                a[i][j][k] = 0;
            }
        }
    }

    #pragma acc parallel loop gang worker private(tmp)
    for (int k = 0; k < n; ++k) {
        for (int j = 0; j < n; ++j) {
            tmp[j][k] = b[j][k] + c[j][k];
            #pragma acc loop vector
            for (int i = 0; i < n; ++i) {
                a[i][j][k] = a[i][j][k] + tmp[j][k];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (a[i][j][k] != (b[j][k] + c[j][k])) {
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