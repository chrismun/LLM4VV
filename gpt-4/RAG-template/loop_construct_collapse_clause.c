#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct collapse clause,V:2.7-3.3
int test1() {
    int errors = 0;
    
    int m = 50;
    int n = 50;
    int p = 50;

    // Allocate space for array
    int* arr = (int*) malloc(sizeof(int) * m * n * p);

    // Off-device computation
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < p; ++k) {
                arr[(i * n * p) + (j * p) + k] = i * j * k;
            }
        }
    }

    // On-device computation
    #pragma acc parallel loop collapse(3)
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < p; ++k) {
                if (arr[(i * n * p) + (j * p) + k] != i * j * k) {
                    errors = 1;
                }
            }
        }
    }

    // Release allocated space
    free(arr);

    return errors;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}