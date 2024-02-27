#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define SEED 12345
#define n 1024
#define PRECISION 0.001

#ifndef T2
// T2: cache, loop, V:1.0-2.7
int test_cache_directive() {
    int err = 0;
    srand(SEED);
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));
    float *c = (float *)malloc(n * sizeof(float));

    for (int i = 0; i < n; ++i) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
        c[i] = 0.0;
    }

    #pragma acc parallel num_gangs(1) vector_length(128)
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i) {
            #pragma acc cache(readonly: a[i], readonly: b[i])
            c[i] = a[i] + b[i];
        }
    }

    for (int i = 0; i < n; ++i) {
        if (fabs(c[i] - (a[i] + b[i])) > PRECISION) {
            err++;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;

#ifndef T2
    failed = test_cache_directive();
    if (failed != 0) {
        failcode |= (1 << 1);
        printf("test_cache_directive failed with %d errors.\n", failed);
    } else {
        printf("test_cache_directive passed.\n");
    }
#endif

    return failcode;
}