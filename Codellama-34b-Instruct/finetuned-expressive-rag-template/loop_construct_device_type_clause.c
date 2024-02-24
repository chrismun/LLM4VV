#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct device_type clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a, *b, *c, *d, *e, *f;
    int num_elements = 1024;

    a = (int *)malloc(num_elements * sizeof(int));
    b = (int *)malloc(num_elements * sizeof(int));
    c = (int *)malloc(num_elements * sizeof(int));
    d = (int *)malloc(num_elements * sizeof(int));
    e = (int *)malloc(num_elements * sizeof(int));
    f = (int *)malloc(num_elements * sizeof(int));

    for (int x = 0; x < num_elements; ++x){
        a[x] = rand() % num_elements;
        b[x] = rand() % num_elements;
        c[x] = 0;
        d[x] = 0;
        e[x] = 0;
        f[x] = 0;
    }

    #pragma acc data copyin(a[0:num_elements], b[0:num_elements]) copyout(c[0:num_elements], d[0:num_elements], e[0:num_elements], f[0:num_elements])
    {
        #pragma acc loop device_type(1)
        for (int x = 0; x < num_elements; ++x){
            c[x] = a[x] + b[x];
        }

        #pragma acc loop device_type(2)
        for (int x = 0; x < num_elements; ++x){
            d[x] = a[x] - b[x];
        }

        #pragma acc loop device_type(3)
        for (int x = 0; x < num_elements; ++x){
            e[x] = a[x] * b[x];
        }

        #pragma acc loop device_type(4)
        for (int x = 0; x < num_elements; ++x){
            if (b[x] != 0)
                f[x] = a[x] / b[x];
        }
    }

    for (int x = 0; x < num_elements; ++x){
        if (c[x] != a[x] + b[x]){
            err += 1;
        }
        if (d[x] != a[x] - b[x]){
            err += 1;
        }
        if (e[x] != a[x] * b[x]){
            err += 1;
        }
        if (b[x] != 0 && f[x] != a[x] / b[x]){
            err += 1;
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