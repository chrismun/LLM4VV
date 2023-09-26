#include <stdio.h>
#include <openacc.h>
#define SIZE 100000

int test() {
    int sum = 0, err = 0;
    int a[SIZE], b[SIZE];

    // initialize arrays
    for (int i = 0; i < SIZE; ++i) {
        a[i] = i;
        b[i] = SIZE - i;
    }

    #pragma acc kernels
    for (int i = 0; i < SIZE; ++i) {
        sum += a[i] * b[i];
    }

    // check results
    int expected = (SIZE - 1) * (SIZE / 2);
    if (sum != expected) {
        printf("Error: expected %d, got %d\n", expected, sum);
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Invoke test function
    failed = test();
    if (failed != 0) {
        failcode += 1;
    }

    return failcode;
}