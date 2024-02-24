#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    const int N = 1000;
    const int M = 1000;
    int a[N][M], b[N][M], c[N][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
        }
    }

    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (c[i][j] != a[i][j] + b[i][j]) {
                err = 1;
                break;
            }
        }
        if (err) break;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}