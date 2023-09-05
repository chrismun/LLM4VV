#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000
#define PRECISION 0.00001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: collapse clause with force modifier
    failed = 0;
    for (int x = 0; x < N; ++x) {
        int err = 0;
        real_t *a = (real_t *)malloc(N * sizeof(real_t));
        real_t *b = (real_t *)malloc(N * sizeof(real_t));

        for (int i = 0; i < N; ++i) {
            a[i] = rand() / (real_t)(RAND_MAX / 10);
            b[i] = 0;
        }

        #pragma acc parallel loop collapse(force:2)
        {
            for (int i = 0; i < N; ++i) {
                real_t tanI = tan(a[i]);
                for (int j = 0; j < N; ++j) {
                    b[j] += tanI;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (fabs(b[i] - a[i]) > PRECISION) {
                err += 1;
            }
        }

        if (err > 0) {
            failed += 1;
        }

        free(a);
        free(b);
    }

    if (failed > 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: collapse clause without force modifier
    failed = 0;
    for (int x = 0; x < N; ++x) {
        int err = 0;
        real_t *a = (real_t *)malloc(N * sizeof(real_t));
        real_t *b = (real_t *)malloc(N * sizeof(real_t));

        for (int i = 0; i < N; ++i) {
            a[i] = rand() / (real_t)(RAND_MAX / 10);
            b[i] = 0;
        }

        #pragma acc parallel loop collapse(2)
        {
            for (int i = 0; i < N; ++i) {
                real_t tanI = tan(a[i]);
                for (int j = 0; j < N; ++j) {
                    b[j] += tanI;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (fabs(b[i] - a[i]) > PRECISION) {
                err += 1;
            }
        }

        if (err > 0) {
            failed += 1;
        }

        free(a);
        free(b);
    }

    if (failed > 0) {
        failcode = failcode + (1 << 1);
    }

    return failcode;
}