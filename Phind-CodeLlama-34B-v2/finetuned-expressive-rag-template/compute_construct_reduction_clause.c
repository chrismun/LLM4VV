#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    const int N = 1000;
    int a[N], b[N], c[N];
    int sum = 0;

    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc parallel loop reduction(+:sum)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
        sum += c[i];
    }

    for (int i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            err = 1;
            break;
        }
    }

    if (sum != 2 * N * (N - 1)) {
        err = 1;
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