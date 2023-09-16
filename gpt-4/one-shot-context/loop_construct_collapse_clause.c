#include "acc_testsuite.h"
#include <math.h>

int test_collapse() {
    const int n = 10000;
    int err = 0;
    int* a = (int*) malloc(n* sizeof(int));
    int* b = (int*) malloc(n* sizeof(int));

    // initialize arrays with different data
    for (int i = 0; i < n; ++i) {
        a[i] = i;
        b[i] = 0;
    }

    // OpenACC loop with collapse
    #pragma acc parallel loop collapse(2) copy(a[0:n], b[0:n])
    for (int i = 0; i < sqrt(n); ++i) {
        for (int j = 0; j < sqrt(n); ++j) {
            int index = i*sqrt(n) + j;
            b[index] = a[index];
        }
    }

    // verification
    for (int i = 0; i < n; ++i) {
        if(a[i] != b[i]) {
            err++;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int err = 0;
    err += test_collapse();

    if (err != 0) {
        printf("Test failed!\n");
    }

    return err;
}