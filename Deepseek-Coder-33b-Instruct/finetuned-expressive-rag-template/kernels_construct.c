#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i, err = 0;

    // Initialize the arrays
    for (i = 0; i < N; ++i) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // Use the kernels construct to square each number in the array
    #pragma acc kernels copyin(a[0:N]) copyout(b[0:N])
    {
        for (i = 0; i < N; ++i) {
            b[i] = a[i] * a[i];
        }
    }

    // Check the results
    for (i = 0; i < N; ++i) {
        if (b[i] != a[i] * a[i]) {
            err = 1;
            break;
        }
    }

    // Return 0 if the target feature, kernels construct, is working properly, and nonzero otherwise
    return err;
}