#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a, *b, *c, *d, *e, *f;
    int num_workers = 4;
    int num_gangs = 2;
    int num_iterations = 1000;
    int i, j;

    a = (int *)malloc(num_iterations * sizeof(int));
    b = (int *)malloc(num_iterations * sizeof(int));
    c = (int *)malloc(num_iterations * sizeof(int));
    d = (int *)malloc(num_iterations * sizeof(int));
    e = (int *)malloc(num_iterations * sizeof(int));
    f = (int *)malloc(num_iterations * sizeof(int));

    for (i = 0; i < num_iterations; ++i){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
        d[i] = 0;
        e[i] = 0;
        f[i] = 0;
    }

    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers) vector_length(128)
    {
        #pragma acc loop worker
        for (i = 0; i < num_iterations; ++i){
            c[i] = a[i] + b[i];
        }

        #pragma acc loop worker(num_workers)
        for (i = 0; i < num_iterations; ++i){
            d[i] = a[i] - b[i];
        }

        #pragma acc loop worker
        for (i = 0; i < num_iterations; ++i){
            e[i] = a[i] * b[i];
        }

        #pragma acc loop worker(num_workers)
        for (i = 0; i < num_iterations; ++i){
            f[i] = a[i] / b[i];
        }
    }

    for (i = 0; i < num_iterations; ++i){
        if (c[i] != a[i] + b[i] || d[i] != a[i] - b[i] || e[i] != a[i] * b[i] || f[i] != a[i] / b[i]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(f);

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