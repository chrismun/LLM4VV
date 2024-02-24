#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int i, err = 0;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    // Initialize arrays
    for (i = 0; i < N; ++i) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // Use OpenACC kernels construct to square each number in the array
    #pragma acc kernels copyin(a[0:N]), copyout(b[0:N])
    for (i = 0; i < N; ++i) {
        b[i] = a[i] * a[i];
    }

    // Check the result
    for (i = 0; i < N; ++i) {
        if (b[i] != a[i] * a[i]) {
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}