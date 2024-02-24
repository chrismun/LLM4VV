#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:compute construct self clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int N = 1000;
    int a[N], b[N], c[N];

    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc data copy(a[0:N], b[0:N], c[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }

        #pragma acc compute self(c[0:N])
        {
            for (int i = 0; i < N; i++) {
                c[i] *= 2;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (c[i] != (a[i] + b[i]) * 2) {
            err = 1;
            break;
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